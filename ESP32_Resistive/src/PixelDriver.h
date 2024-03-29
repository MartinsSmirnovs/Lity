#pragma once

#include "RGB.h"

namespace PixelDriver
{

void setup();
void setColor( int pixel, const struct RGB& color );
void show();
} // namespace PixelDriver
