#pragma once

// Deterministic sin, cos and acos for the gameplay simulation.
//
// The C library's versions differ in the last bit between MSVC, glibc and Apple's libm, which is enough for a
// replay recorded on one system to drift on another. These are ports of fdlibm (FreeBSD msun), using only +, -,
// *, / and sqrt, which IEEE 754 defines exactly, so every platform gets the same bits. The build turns off
// floating-point contraction (fused multiply-add) for the same reason.
namespace dmath
{

double sin(double x);
double cos(double x);
double acos(double x);

}
