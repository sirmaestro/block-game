#include "voxels.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

bool VoxelText::build(const Gfx &gfx, std::string_view s)
{
    int total = 0;
    for (const char c : s)
    {
        total += Gfx::glyph_width(c) + 1;
    }
    int offset = -((total - 1) / 2);

    for (const char c : s)
    {
        const int w = Gfx::glyph_width(c);
        const auto uc = static_cast<unsigned char>(c);
        if (c != ' ' && uc >= 0x21 && uc <= 0x7e)
        {
            const int base = uc < 0x40 ? 0x21 : uc < 0x60 ? 0x40 : 0x60;
            const int cell_x = (uc - base) * 18;
            const int cell_y = uc < 0x40 ? 0 : uc < 0x60 ? 16 : 32;
            for (int row = 0; row < 16; ++row)
            {
                for (int col = 0; col <= w + 1; ++col)
                {
                    const int kind = gfx.font_pixel_kind(cell_x + col, cell_y + row);
                    if (kind < 0)
                    {
                        continue;
                    }
                    if (voxels.size() >= max_voxels)
                    {
                        return false;
                    }
                    voxels.push_back({(col + offset) * 8.0, 48.0 - 8.0 * row, 0.0, 0.0, 0.0, kind});
                }
            }
        }
        offset += w + 1;
    }
    return true;
}

void VoxelText::rotate_x(double radians, std::size_t first)
{
    const double s = std::sin(radians), c = std::cos(radians);
    for (auto i = first; i < voxels.size(); ++i)
    {
        auto &v = voxels[i];
        const double y = v.y;
        v.y = y * c - v.z * s;
        v.z = y * s + v.z * c;
    }
}

void VoxelText::rotate_y(double radians, std::size_t first)
{
    const double s = std::sin(radians), c = std::cos(radians);
    for (auto i = first; i < voxels.size(); ++i)
    {
        auto &v = voxels[i];
        const double x = v.x;
        v.x = x * c - v.z * s;
        v.z = x * s + v.z * c;
    }
}

void VoxelText::rotate_z(double radians, double pivot_x)
{
    const double s = std::sin(radians), c = std::cos(radians);
    for (auto &v : voxels)
    {
        const double x = v.x - pivot_x;
        v.x = x * c - v.y * s + pivot_x;
        v.y = x * s + v.y * c;
    }
}

const std::vector<int> &VoxelText::depth_order()
{
    order_.resize(voxels.size());
    std::iota(order_.begin(), order_.end(), 0);
    scratch_.resize(voxels.size());
    if (!order_.empty())
    {
        merge_sort(0, static_cast<int>(order_.size()) - 1);
    }
    return order_;
}

// Same recursion and tie-breaking as FUN_00404940/FUN_00404a10: descending z, and on
// left.z <= right.z the right element is taken first.
void VoxelText::merge_sort(int lo, int hi)
{
    if (lo >= hi)
    {
        return;
    }
    const int mid = (lo + hi) / 2;
    merge_sort(lo, mid);
    merge_sort(mid + 1, hi);

    int l = lo, r = mid + 1, out = lo;
    while (l <= mid && r <= hi)
    {
        if (voxels[order_[l]].z <= voxels[order_[r]].z)
        {
            scratch_[out++] = order_[r++];
        }
        else
        {
            scratch_[out++] = order_[l++];
        }
    }
    while (l <= mid)
    {
        scratch_[out++] = order_[l++];
    }
    while (r <= hi)
    {
        scratch_[out++] = order_[r++];
    }
    std::copy(scratch_.begin() + lo, scratch_.begin() + hi + 1, order_.begin() + lo);
}
