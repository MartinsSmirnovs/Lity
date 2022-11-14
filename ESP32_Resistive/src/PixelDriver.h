#pragma once
#ifdef BUILD_ESP32

#include "RGB.h"
#include <Adafruit_NeoPixel.h>

class PixelDriver {
public:
    PixelDriver();

    void setup();
    void setColor(int pixel, const RGB& color);

private:
    Adafruit_NeoPixel strip;
};

#endif
