# Turns a file into a C++ source defining `std::span<const std::uint8_t> <NAME>()`.
# Usage: cmake -DINPUT=<file> -DOUTPUT=<file.cpp> -DNAME=<symbol> -P embed.cmake
file(READ "${INPUT}" hex HEX)
string(LENGTH "${hex}" hex_length)
math(EXPR size "${hex_length} / 2")
string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," bytes "${hex}")
string(REGEX REPLACE "((0x..,){32})" "\\1\n    " bytes "${bytes}")

file(WRITE "${OUTPUT}" "// generated from ${INPUT} by cmake/embed.cmake - do not edit
#include <cstdint>
#include <span>

namespace assets
{

namespace
{
alignas(4) const std::uint8_t data[${size}] = {
    ${bytes}
};
}

std::span<const std::uint8_t> ${NAME}()
{
    return data;
}

}
")
