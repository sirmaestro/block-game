#pragma once

#include <array>
#include <string_view>
#include <vector>

#include "gfx.hpp"

// The original's "3D display": text whose font pixels become 8x8 dot sprites, rotated and projected.
struct Voxel
{
    double x;
    double y;
    double z;
    double vx;
    double vy;
    int kind; // 0 = glyph face, 1 = glyph outline
};

class VoxelText
{
  public:
    static constexpr std::size_t max_voxels = 2000;

    void clear()
    {
        voxels.clear();
    }

    // Appends voxels for `s` (centred on x = 0, rows y = 48 .. -72, z = 0). Returns false when full.
    bool build(const Gfx &gfx, std::string_view s);

    void rotate_x(double radians, std::size_t first = 0);
    void rotate_y(double radians, std::size_t first = 0);
    void rotate_z(double radians, double pivot_x);

    // Painter's order: farthest (largest z) first; ties resolved like the original merge sort.
    const std::vector<int> &depth_order();

    std::vector<Voxel> voxels;
    std::array<Rect, 3> rects{};

  private:
    void merge_sort(int lo, int hi);

    std::vector<int> order_;
    std::vector<int> scratch_;
};
