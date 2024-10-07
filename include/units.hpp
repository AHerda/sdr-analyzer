#pragma once

#include <cstdint>

constexpr uint32_t operator"" _MHz(unsigned long long value) {
    return static_cast<uint32_t>(value * 1'000'000);
}

constexpr uint32_t operator"" _kHz(unsigned long long value) {
    return static_cast<uint32_t>(value * 1'000);
}

// uint32_t operator"" _MHz(double value) {
//     return static_cast<uint32_t>(value * 1'000'000);
// }
