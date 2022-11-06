#pragma once

#include <stdint.h>

struct RGB {
    RGB() = default;

    RGB(uint8_t red, uint8_t green, uint8_t blue)
    : red(red),
      green(green),
      blue(blue) {
    }

    uint8_t red   = 0;
    uint8_t green = 0;
    uint8_t blue  = 0;

    bool operator==(const RGB& first) const {
        return red == first.red && green == first.green && blue == first.blue;
    }

    constexpr static int colorsInPixel = 3;
};
