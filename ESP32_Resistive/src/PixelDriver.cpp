#include "PixelDriver.h"
#include "LityConfig.h"
#include <FastLED.h>

namespace PixelDriver
{

static CRGB leds[ fieldsCount ];

void setup()
{
    FastLED.addLeds< NEOPIXEL, GPIO_NUM_5 >( leds, fieldsCount );
    FastLED.clear();
    FastLED.show();
}

void setColor( int pixel, const struct RGB& color )
{
    leds[ pixel ].setRGB( color.red, color.green, color.blue );
    FastLED.show();
}

} // namespace PixelDriver
