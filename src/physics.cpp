// Gameplay simulation: FUN_004029f0 (physics step, run twice per frame) and FUN_00401900 (items, debris,
// ball-spawning blocks). See re/notes/physics.md.
#include "game.hpp"

#include <cmath>

namespace
{

constexpr double fps = Game::ticks_per_second;
constexpr double two_pi = 6.28318530718;            // literal used by the original
constexpr double deg_to_rad = 0.017453292519944444; // literal used by the original
constexpr double normal_gravity = 0.017;
constexpr double reversed_gravity = -0.085;

// Angle of (dx, dy) in [0, 2pi), y down; the original's acos-based formula.
double direction(double dx, double dy)
{
    const double length = std::sqrt(dx * dx + dy * dy);
    double angle = std::acos(dx / length);
    if (dy / length < 0.0)
    {
        angle = two_pi - angle;
    }
    return angle;
}

}

// ---- paddle ---------------------------------------------------------------------------------------------

void Game::update_paddle()
{
    const Point m = cursor();
    const int old_x = paddle_x_;
    paddle_x_ = m.x;
    paddle_tilt_ = (m.x + paddle_tilt_ - old_x) * 0.5;

    const int lo = 8 * paddle_units_ + 16;
    const int hi = (62 - paddle_units_) * 8;
    if (m.x < lo)
    {
        paddle_x_ = lo;
        set_cursor(lo, m.y);
    }
    else if (m.x > hi)
    {
        paddle_x_ = hi;
        set_cursor(hi, m.y);
    }

    if (!left_down_)
    {
        if (paddle_y_ <= 440.0)
        {
            paddle_vy_ = 0.0;
            paddle_y_ = 440.0;
        }
        else
        {
            paddle_vy_ = -2.0;
        }
    }
    else
    {
        if (paddle_y_ >= 472.0)
        {
            paddle_vy_ = 0.0;
            paddle_y_ = 472.0;
        }
        else
        {
            paddle_vy_ = 2.0;
        }
    }
    paddle_y_ += paddle_vy_ * 100.0 / fps;
}

// ---- collision helpers ----------------------------------------------------------------------------------

bool Game::ball_overlaps_block(int k, double x, double y, int r) const
{
    const auto &b = blocks_[k];
    const double cx = b.fx[0] + 14.0, cy = b.fy[0] + 6.0;
    const double l = cx - 16.0, rt = cx + 16.0, t = cy - 8.0, bt = cy + 8.0;
    const double rr = double(r) * r;
    const auto d2 = [&](double px, double py) { return (px - x) * (px - x) + (py - y) * (py - y); };

    return (l - r < x && x < rt + r && t < y && y < bt) || (l < x && x < rt && t - r < y && y < bt + r) ||
           d2(l, t) < rr || d2(rt, t) < rr || d2(rt, bt) < rr || d2(l, bt) < rr;
}

// The 3x3 neighbourhood test used before a ball may change size.
bool Game::ball_overlaps_any_block(double x, double y, int r) const
{
    const int col = static_cast<int>((x - 16.0) / 32.0);
    const int row = static_cast<int>((y - 16.0) / 16.0);
    for (int ro = 0; ro < 3; ++ro)
    {
        for (int co = 0; co < 3; ++co)
        {
            const int k = (row - 1 + ro) * stages::columns + (col - 1 + co);
            if (k >= 0 && k < int(blocks_.size()) && blocks_[k].state == block_alive && ball_overlaps_block(k, x, y, r))
            {
                return true;
            }
        }
    }
    return false;
}

// Which part of the block outline the ball came through: 0 top, 1 top-right, 2 right, 3 bottom-right,
// 4 bottom, 5 bottom-left, 6 left, 7 top-left. Corners next to covered sides become faces.
int Game::hit_octant(int k, double x, double y, double vx, double vy, int r)
{
    const auto &b = blocks_[k];
    const double cx = b.fx[0] + 14.0, cy = b.fy[0] + 6.0;
    const double l = cx - 16.0, rt = cx + 16.0, t = cy - 8.0, bt = cy + 8.0;
    const double px[8] = {l, rt, rt + r, rt + r, rt, l, l - r, l - r};
    const double py[8] = {t - r, t - r, t, bt, bt + r, bt + r, bt, t};

    double theta[8];
    for (int i = 0; i < 8; ++i)
    {
        theta[i] = direction(px[i] - x, py[i] - y);
    }
    const double phi = direction(-vx, -vy);

    // the segment variable persists between calls in the original; an undefined result keeps the old value
    for (int i = 0; i < 8; ++i)
    {
        const int j = (i + 1) % 8;
        if ((theta[j] < theta[i] && ((theta[i] <= phi && phi < two_pi) || (0.0 <= phi && phi < theta[j]))) ||
            (theta[i] <= phi && phi < theta[j]))
        {
            hit_seg_ = i;
        }
    }

    int seg = hit_seg_;
    if (b.covered & 1)
    {
        seg = seg == 7 ? 0 : seg == 5 ? 4 : seg;
    }
    if (b.covered & 2)
    {
        seg = seg == 1 ? 2 : seg == 7 ? 6 : seg;
    }
    if (b.covered & 4)
    {
        seg = seg == 1 ? 0 : seg == 3 ? 4 : seg;
    }
    if (b.covered & 8)
    {
        seg = seg == 3 ? 2 : seg == 5 ? 6 : seg;
    }
    hit_seg_ = seg;
    return seg;
}

// LAB_00403fbb
void Game::destroy_block(int k, double x, double y, double vx, double vy)
{
    auto &b = blocks_[k];
    play(Sfx::block);

    if (b.type == 6 || b.type == 9)
    {
        b.state = block_spawning;
        dying_.push_back(k);
    }
    else
    {
        b.state = block_breaking;
        if (data_.show_broken_blocks)
        {
            dying_.push_back(k);
        }
    }

    if (b.type == 7 || b.type == 8)
    {
        items_.push_back({b.fx[0] + 14.0, b.fy[0] + 6.0, 0.0, -1.0, rand() % 7, item_falling});
    }

    const int col = k % stages::columns;
    if (col != 0)
    {
        blocks_[k - 1].covered &= ~4u;
    }
    if (k >= stages::columns)
    {
        blocks_[k - stages::columns].covered &= ~8u;
    }
    if (col != stages::columns - 1)
    {
        blocks_[k + 1].covered &= ~1u;
    }
    if (k < int(blocks_.size()) - stages::columns)
    {
        blocks_[k + stages::columns].covered &= ~2u;
    }
    --remaining_;

    if (data_.show_broken_blocks)
    {
        // fragments fly away from the impact point: 8 * speed^2 * direction / distance^1.6
        const double s2 = vx * vx + vy * vy;
        for (int f = 0; f < 32; ++f)
        {
            const double dx = b.fx[f] - x, dy = b.fy[f] - y;
            const double d2 = dx * dx + dy * dy;
            const double d = std::sqrt(d2);
            b.fvx[f] = (dx / d) * s2 * 8.0 / std::pow(d2, 0.8);
            b.fvy[f] = (dy / d) * s2 * 8.0 / std::pow(d2, 0.8);
        }
    }
}

// ---- physics step (FUN_004029f0) ------------------------------------------------------------------------

void Game::physics_step()
{
    update_paddle();

    const int target_r = ball_radius_;
    const int half_w = 8 * paddle_units_;

    for (std::size_t i = 0; i < balls_.size();)
    {
        Ball &ball = balls_[i];
        const double x0 = ball.x, y0 = ball.y;
        double vx = ball.vx;
        double vy = ball.vy + gravity_ * 100.0 / fps;

        // black blocks (types 10, 11) push balls away, inverse square
        for (int k = 0; k < int(blocks_.size()); ++k)
        {
            const auto &b = blocks_[k];
            if ((b.type == 10 || b.type == 11) && b.state == block_alive)
            {
                const double cx = b.fx[0] + 14.0, cy = b.fy[0] + 6.0;
                const double dx = ball.x - cx, dy = ball.y - cy;
                const double d2 = dx * dx + dy * dy;
                const double d = std::sqrt(d2);
                const double a = (-17.0 / d2) * 100.0 / fps;
                vx += ((cx - ball.x) / d) * a;
                vy += ((cy - ball.y) / d) * a;
            }
        }

        double x = ball.x + vx * 100.0 / fps;
        double y = ball.y + vy * 100.0 / fps;

        // a ball takes a new size (big/small items) only once it has room
        if (ball.r != target_r)
        {
            const bool near_paddle = paddle_x_ - half_w - target_r < x && x < paddle_x_ + half_w + target_r &&
                                     paddle_y_ - 8.0 - target_r < y && y < paddle_y_ + 16.0;
            const bool inside = target_r + 16 <= x && x <= 496 - target_r && target_r + 16 <= y &&
                                y <= 480 - target_r;
            if (!near_paddle && inside && !ball_overlaps_any_block(x, y, target_r))
            {
                play(target_r > ball.r ? Sfx::big : Sfx::small);
                ball.r = target_r;
            }
        }
        const int r = ball.r;

        // paddle
        if (paddle_x_ - half_w < x && x <= paddle_x_ + half_w && paddle_y_ - 8.0 - r < y && y <= paddle_y_ + 16.0)
        {
            play(Sfx::pad);
            const double s = std::sin(paddle_tilt_ * deg_to_rad), c = std::cos(paddle_tilt_ * deg_to_rad);
            const double relative = paddle_vy_ - vy;
            const double nvx = c * vx - relative * s;
            const double nvy = vx * s + relative * c;
            vx = nvx;
            vy = nvy;
            if (vy > -3.7 && gravity_ > 0.0)
            {
                vy = -3.7;
            }
            else if (vy < -6.5)
            {
                vy = -6.5;
            }
            if (vx > 4.0)
            {
                vx = 4.0;
            }
            else if (vx < -4.0)
            {
                vx = -4.0;
            }
            y = paddle_y_ - 8.0 - r;
        }

        // walls and ceiling; the original's reflection formula divides by the step, guarded here
        const double lo = r + 16.0, hi = 496.0 - r;
        if (x < lo)
        {
            vx *= -0.95;
            x = x != x0 ? (x - lo) * vx / (x - x0) + lo : lo;
        }
        if (x > hi)
        {
            vx *= -0.95;
            x = x != x0 ? (x - hi) * vx / (x - x0) + hi : hi;
        }
        if (y < lo)
        {
            vy *= -0.95;
            y = y != y0 ? (y - lo) * vy / (y - y0) + lo : lo;
        }
        if (y > 480.0 - r)
        {
            balls_.erase(balls_.begin() + static_cast<std::ptrdiff_t>(i));
            continue;
        }

        // blocks in the 3x3 neighbourhood; the cell is recomputed from the current position each time
        bool up = false, down = false, left = false, right = false;
        for (int ro = 0; ro < 3; ++ro)
        {
            for (int co = 0; co < 3; ++co)
            {
                const int row = static_cast<int>((y - 16.0) / 16.0);
                const int col = static_cast<int>((x - 16.0) / 32.0);
                const int k = (row - 1 + ro) * stages::columns + (col - 1 + co);
                if (k < 0 || k >= int(blocks_.size()) || blocks_[k].state != block_alive ||
                    !ball_overlaps_block(k, x, y, r))
                {
                    continue;
                }

                auto &b = blocks_[k];
                const int type = b.type;
                bool reflect = false;
                int seg = 0;

                const auto damage = [&](int new_type) {
                    play(Sfx::block2);
                    b.type = new_type;
                };

                // hit: damage, arrows, silver, or destroy; then decide whether the ball bounces
                bool post = true;
                if (type == 0 && r == 4)
                {
                    damage(1);
                }
                else if (type == 2 && r != 16)
                {
                    damage(r == 4 ? 3 : 4);
                }
                else if (type == 3 && r == 4)
                {
                    damage(4);
                }
                else if (type == 5)
                {
                    play(Sfx::pad);
                }
                else if (type == 10 && r == 4)
                {
                    damage(11);
                }
                else if (type == 7 && r == 4)
                {
                    damage(8);
                }
                else if (type == 12)
                {
                    up = true;
                    continue;
                }
                else if (type == 13)
                {
                    down = true;
                    continue;
                }
                else if (type == 14)
                {
                    left = true;
                    continue;
                }
                else if (type == 15)
                {
                    right = true;
                    continue;
                }
                else if (type == 16 || type == 17)
                {
                    // silver: only breakable from above
                    seg = hit_octant(k, x, y, vx, vy, r);
                    post = false;
                    if (seg != 0 && seg != 1 && seg != 7)
                    {
                        play(Sfx::pad);
                        reflect = true;
                    }
                    else if (type == 16 && r == 4)
                    {
                        b.type = 17;
                        play(Sfx::block2);
                        reflect = true;
                    }
                    else
                    {
                        destroy_block(k, x, y, vx, vy);
                        post = true;
                    }
                }
                else
                {
                    destroy_block(k, x, y, vx, vy);
                }

                if (post)
                {
                    // LAB_004042a1: bounce rules by the (possibly damaged) type
                    switch (b.type)
                    {
                        case 0: case 4: case 7: case 10:
                            reflect = r != 16;
                            break;
                        case 1: case 8: case 11:
                            reflect = r == 4;
                            break;
                        case 16:
                            reflect = r != 16; // already destroyed from above; octant known
                            break;
                        case 17:
                            reflect = r == 4;
                            break;
                        default:
                            reflect = true;
                            break;
                    }
                    if (reflect && b.type != 16 && b.type != 17)
                    {
                        seg = hit_octant(k, x, y, vx, vy, r);
                    }
                }
                if (!reflect)
                {
                    continue;
                }

                // LAB_004042f3: reflect and push out
                const double cx = b.fx[0] + 14.0, cy = b.fy[0] + 6.0;
                const double l = cx - 16.0, rt = cx + 16.0, t = cy - 8.0, bt = cy + 8.0;
                switch (seg)
                {
                    case 0:
                        vy = -vy * 0.95;
                        y = t - r;
                        break;
                    case 2:
                        vx = -vx * 0.95;
                        x = rt + r;
                        break;
                    case 4:
                        vy = -vy * 0.95;
                        y = bt + r;
                        break;
                    case 6:
                        vx = -vx * 0.95;
                        x = l - r;
                        break;
                    default:
                    {
                        const double ex = seg == 1 || seg == 3 ? rt : l;
                        const double ey = seg == 1 || seg == 7 ? t : bt;
                        const double d = std::sqrt((y - ey) * (y - ey) + (x - ex) * (x - ex));
                        const double nx = (ex - x) / d, ny = (ey - y) / d;
                        const double tangential = vy * nx - vx * ny;
                        const double normal = (vx * nx + vy * ny) * 0.95;
                        vx = -tangential * ny - normal * nx;
                        vy = tangential * nx - normal * ny;
                        x = ex - r * nx;
                        y = ey - r * ny;
                        break;
                    }
                }
            }
        }

        if (up)
        {
            vy = -2.0;
        }
        else if (down)
        {
            vy = 2.0;
        }
        if (left)
        {
            vx = -2.0;
        }
        else if (right)
        {
            vx = 2.0;
        }

        ball.x = x;
        ball.y = y;
        ball.vx = vx;
        ball.vy = vy;
        ++i;
    }
}

// ---- items, debris and ball fountains (FUN_00401900) ----------------------------------------------------

void Game::update_items_and_debris()
{
    for (auto &item : items_)
    {
        if (item.state == item_falling)
        {
            item.vy += 1.7000000000000002 / fps;
            item.y += item.vy * 100.0 / fps;
            if (item.y > 488.0)
            {
                item.state = item_gone;
            }
            const int reach = paddle_units_ * 8 + 16;
            if (paddle_x_ - reach < item.x && item.x < paddle_x_ + reach && paddle_y_ - 16.0 < item.y &&
                item.y < paddle_y_ + 16.0)
            {
                switch (item.type)
                {
                    case 0: // big ball
                        ball_radius_ = 16;
                        big_ms_ += 10000;
                        small_ms_ = 0;
                        break;
                    case 1: // small ball
                        ball_radius_ = 4;
                        small_ms_ += 10000;
                        big_ms_ = 0;
                        break;
                    case 2: // longer paddle
                        play(Sfx::item);
                        if (paddle_units_ < 28)
                        {
                            paddle_units_ += 3;
                        }
                        break;
                    case 3: // shorter paddle
                        play(Sfx::item);
                        if (paddle_units_ > 5)
                        {
                            paddle_units_ -= 3;
                        }
                        break;
                    case 4: // full-width paddle
                        play(Sfx::item);
                        paddle_units_ = 30;
                        break;
                    case 5: // reverse gravity
                        play(Sfx::reverse);
                        gravity_ = reversed_gravity;
                        reverse_ms_ += 5000;
                        break;
                    case 6: // infinite balls
                        stop(Sfx::bgm);
                        play(Sfx::mugen, true);
                        infinite_ = true;
                        mugen_ms_ += 20000;
                        break;
                }
                item.state = item_to_hud;
            }
        }
        else if (item.state == item_to_hud)
        {
            double tx = 544.0, ty = 344.0;
            switch (item.type)
            {
                case 2: case 3: case 4:
                    ty = 360.0;
                    break;
                case 5:
                    ty = 376.0;
                    break;
                case 6:
                    tx = 568.0;
                    ty = 288.0;
                    break;
            }
            const double dx = tx - item.x, dy = ty - item.y;
            const double d = std::sqrt(dx * dx + dy * dy);
            item.vx = d != 0.0 ? d * (dx / d) * 0.03333333333333333 : 0.0;
            item.vy = d != 0.0 ? d * (dy / d) * 0.03333333333333333 : 0.0;
            item.x += item.vx * 100.0 / fps;
            item.y += item.vy * 100.0 / fps;
            if (static_cast<int>(item.vx * 100.0) == 0 && static_cast<int>(item.vy * 100.0) == 0)
            {
                item.state = item_in_hud;
            }
        }
        else if (item.state == item_in_hud)
        {
            // the effect ends when its HUD icon falls away
            const int t = item.type;
            if (t == 0 && ball_radius_ == 4)
            {
                item.state = item_falling;
            }
            else if (t == 1 && ball_radius_ == 16)
            {
                item.state = item_falling;
            }
            else if ((t == 0 && big_ms_ < 1) || (t == 1 && small_ms_ < 1))
            {
                item.state = item_falling;
                ball_radius_ = 8;
            }
            else if (t == 2 && (paddle_units_ < 7 || paddle_units_ == 30))
            {
                item.state = item_falling;
            }
            else if (t == 3 && paddle_units_ > 5)
            {
                item.state = item_falling;
            }
            else if (t == 4 && paddle_units_ < 7)
            {
                item.state = item_falling;
            }
            else if (t == 5 && reverse_ms_ < 1)
            {
                play(Sfx::change);
                item.state = item_falling;
                gravity_ = normal_gravity;
            }
            else if (t == 6 && mugen_ms_ < 1)
            {
                stop(Sfx::mugen);
                play(Sfx::bgm, true);
                item.state = item_falling;
                infinite_ = false;
            }
        }
    }

    // Red and cyan blocks spawn one ball per frame each (red once, cyan until the stage ends) while there are
    // fewer than 500 balls. The original walked them in the order they broke, so once the cap was reached the
    // few slots freed each frame always went to the earliest fountains and later ones never fired. The rebuild
    // shares the free slots round-robin instead.
    std::vector<int> spawners;
    for (const int k : dying_)
    {
        if (blocks_[k].state == block_spawning)
        {
            spawners.push_back(k);
        }
    }
    for (std::size_t i = 0; i < spawners.size() && balls_.size() < 500; ++i)
    {
        auto &b = blocks_[spawners[(spawn_rotor_ + i) % spawners.size()]];
        play(Sfx::ball);
        double vx = (5 - rand() % 11) * 0.3;
        const double vy = (3 - rand() % 11) * 0.3;
        if (vx == 0.0)
        {
            vx = 0.1;
        }
        balls_.push_back({b.fx[0] + 14.0, b.fy[0] + 6.0, vx, vy, 8});
        if (b.type == 6)
        {
            b.state = block_breaking; // red: one ball, then debris
        }
        ++spawn_rotor_;
    }

    // breaking blocks shed fragments
    for (std::size_t n = 0; n < dying_.size(); ++n)
    {
        auto &b = blocks_[dying_[n]];
        if (b.state == block_spawning)
        {
            continue;
        }

        bool any_alive = false;
        for (int f = 0; f < 32; ++f)
        {
            if (!b.alive[f])
            {
                continue;
            }
            any_alive = true;
            b.fvy[f] += gravity_ * 200.0 / fps;
            b.fx[f] += b.fvx[f] * 100.0 / fps;
            b.fy[f] += b.fvy[f] * 100.0 / fps;
            if (gravity_ > 0.0)
            {
                if (b.fy[f] > 478.0 || b.fx[f] < 2.0 || b.fx[f] > 638.0)
                {
                    b.alive[f] = false;
                }
            }
            else if (gravity_ < 0.0 && b.fy[f] < 2.0)
            {
                b.alive[f] = false;
            }
        }
        if (!any_alive)
        {
            // like the original, the entry that moves into this slot is skipped until next frame
            dying_.erase(dying_.begin() + static_cast<std::ptrdiff_t>(n));
        }
    }
}
