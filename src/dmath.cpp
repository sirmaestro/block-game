// Ported from FreeBSD msun (k_sin.c, k_cos.c, e_rem_pio2.c, e_acos.c), originally:
//
// Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
// Developed at SunSoft, a Sun Microsystems, Inc. business.
// Permission to use, copy, modify, and distribute this software is freely granted, provided that this notice
// is preserved.
#include "dmath.hpp"

#include <bit>
#include <cmath>
#include <cstdint>

namespace dmath
{

namespace
{

std::uint32_t high_word(double x)
{
    return static_cast<std::uint32_t>(std::bit_cast<std::uint64_t>(x) >> 32);
}

double with_low_word_cleared(double x)
{
    return std::bit_cast<double>(std::bit_cast<std::uint64_t>(x) & 0xffffffff00000000ull);
}

// sin(x + y) for |x| <= pi/4, y the tail of x; iy == 0 means y is zero.
double kernel_sin(double x, double y, int iy)
{
    constexpr double S1 = -1.66666666666666324348e-01;
    constexpr double S2 = 8.33333333332248946124e-03;
    constexpr double S3 = -1.98412698298579493134e-04;
    constexpr double S4 = 2.75573137070700676789e-06;
    constexpr double S5 = -2.50507602534068634195e-08;
    constexpr double S6 = 1.58969099521155010221e-10;

    const double z = x * x;
    const double w = z * z;
    const double r = S2 + z * (S3 + z * S4) + z * w * (S5 + z * S6);
    const double v = z * x;
    if (iy == 0)
    {
        return x + v * (S1 + z * r);
    }
    return x - ((z * (0.5 * y - v * r) - y) - v * S1);
}

// cos(x + y) for |x| <= pi/4.
double kernel_cos(double x, double y)
{
    constexpr double C1 = 4.16666666666666019037e-02;
    constexpr double C2 = -1.38888888888741095749e-03;
    constexpr double C3 = 2.48015872894767294178e-05;
    constexpr double C4 = -2.75573143513906633035e-07;
    constexpr double C5 = 2.08757232129817482790e-09;
    constexpr double C6 = -1.13596475577881948265e-11;

    const double z = x * x;
    double w = z * z;
    const double r = z * (C1 + z * (C2 + z * C3)) + w * w * (C4 + z * (C5 + z * C6));
    const double hz = 0.5 * z;
    w = 1.0 - hz;
    return w + (((1.0 - w) - hz) + (z * r - x * y));
}

// x - n * pi/2 as y0 + y1, returning n. The medium-size reduction, good to |x| ~ 2^20 * pi/2, far beyond what
// the game passes in.
int rem_pio2(double x, double &y0, double &y1)
{
    constexpr double invpio2 = 6.36619772367581382433e-01;
    constexpr double pio2_1 = 1.57079632673412561417e+00;
    constexpr double pio2_1t = 6.07710050650619224932e-11;
    constexpr double pio2_2 = 6.07710050630396597660e-11;
    constexpr double pio2_2t = 2.02226624879595063154e-21;
    constexpr double pio2_3 = 2.02226624871116645580e-21;
    constexpr double pio2_3t = 8.47842766036889956997e-32;
    constexpr double round_bias = 6755399441055744.0; // 0x1.8p52: adding and subtracting rounds to an integer

    const std::uint32_t ix = high_word(x) & 0x7fffffff;
    volatile double biased = x * invpio2 + round_bias; // volatile: keep the rounding step
    const double fn = biased - round_bias;
    const int n = static_cast<int>(fn);

    double r = x - fn * pio2_1;
    double w = fn * pio2_1t;
    const int j = static_cast<int>(ix >> 20);
    y0 = r - w;
    int i = j - static_cast<int>((high_word(y0) >> 20) & 0x7ff);
    if (i > 16)
    {
        // 2nd iteration, good to 118 bits
        double t = r;
        w = fn * pio2_2;
        r = t - w;
        w = fn * pio2_2t - ((t - r) - w);
        y0 = r - w;
        i = j - static_cast<int>((high_word(y0) >> 20) & 0x7ff);
        if (i > 49)
        {
            // 3rd iteration, 151 bits
            t = r;
            w = fn * pio2_3;
            r = t - w;
            w = fn * pio2_3t - ((t - r) - w);
            y0 = r - w;
        }
    }
    y1 = (r - y0) - w;
    return n;
}

}

double sin(double x)
{
    const std::uint32_t ix = high_word(x) & 0x7fffffff;
    if (ix <= 0x3fe921fb) // |x| ~<= pi/4
    {
        if (ix < 0x3e500000) // |x| < 2^-26
        {
            return x;
        }
        return kernel_sin(x, 0.0, 0);
    }
    if (ix >= 0x7ff00000)
    {
        return x - x; // NaN
    }
    double y0 = 0.0, y1 = 0.0;
    switch (rem_pio2(x, y0, y1) & 3)
    {
        case 0: return kernel_sin(y0, y1, 1);
        case 1: return kernel_cos(y0, y1);
        case 2: return -kernel_sin(y0, y1, 1);
        default: return -kernel_cos(y0, y1);
    }
}

double cos(double x)
{
    const std::uint32_t ix = high_word(x) & 0x7fffffff;
    if (ix <= 0x3fe921fb)
    {
        if (ix < 0x3e46a09e) // |x| < 2^-27 * sqrt(2)
        {
            return 1.0;
        }
        return kernel_cos(x, 0.0);
    }
    if (ix >= 0x7ff00000)
    {
        return x - x;
    }
    double y0 = 0.0, y1 = 0.0;
    switch (rem_pio2(x, y0, y1) & 3)
    {
        case 0: return kernel_cos(y0, y1);
        case 1: return -kernel_sin(y0, y1, 1);
        case 2: return -kernel_cos(y0, y1);
        default: return kernel_sin(y0, y1, 1);
    }
}

double acos(double x)
{
    constexpr double pi = 3.14159265358979311600e+00;
    constexpr double pio2_hi = 1.57079632679489655800e+00;
    constexpr double pio2_lo = 6.12323399573676603587e-17;
    constexpr double pS0 = 1.66666666666666657415e-01;
    constexpr double pS1 = -3.25565818622400915405e-01;
    constexpr double pS2 = 2.01212532134862925881e-01;
    constexpr double pS3 = -4.00555345006794114027e-02;
    constexpr double pS4 = 7.91534994289814532176e-04;
    constexpr double pS5 = 3.47933107596021167570e-05;
    constexpr double qS1 = -2.40339491173441421878e+00;
    constexpr double qS2 = 2.02094576023350569471e+00;
    constexpr double qS3 = -6.88283971605453293030e-01;
    constexpr double qS4 = 7.70381505559019352791e-02;

    const auto rational = [&](double z) {
        const double p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        const double q = 1.0 + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        return p / q;
    };

    const std::uint32_t hx = high_word(x);
    const std::uint32_t ix = hx & 0x7fffffff;
    if (ix >= 0x3ff00000) // |x| >= 1
    {
        if (x == 1.0)
        {
            return 0.0;
        }
        if (x == -1.0)
        {
            return pi + 2.0 * pio2_lo;
        }
        return (x - x) / (x - x); // NaN
    }
    if (ix < 0x3fe00000) // |x| < 0.5
    {
        if (ix <= 0x3c600000) // |x| < 2^-57
        {
            return pio2_hi + pio2_lo;
        }
        const double r = rational(x * x);
        return pio2_hi - (x - (pio2_lo - x * r));
    }
    if (hx & 0x80000000) // x <= -0.5
    {
        const double z = (1.0 + x) * 0.5;
        const double s = std::sqrt(z);
        const double w = rational(z) * s - pio2_lo;
        return pi - 2.0 * (s + w);
    }
    // x >= 0.5
    const double z = (1.0 - x) * 0.5;
    const double s = std::sqrt(z);
    const double df = with_low_word_cleared(s);
    const double c = (z - df * df) / (s + df);
    const double w = rational(z) * s + c;
    return 2.0 * (df + w);
}

}
