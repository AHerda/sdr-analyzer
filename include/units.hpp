#pragma once

#include <cstdint>

constexpr uint32_t operator"" _MHz(unsigned long long value) {
    return value * 1'000'000;
}
