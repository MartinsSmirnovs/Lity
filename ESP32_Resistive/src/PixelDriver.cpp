#include "PixelDriver.h"
#include "LityConfig.h"

PixelDriver::PixelDriver()
: strip( fieldsCount, GPIO_NUM_25, NEO_GRB + NEO_KHZ400 )
{
}

void PixelDriver::setup()
{
    strip.begin();
    strip.clear();
    strip.show();
}

void PixelDriver::setColor( int pixel, const RGB& color )
{
    strip.setPixelColor( pixel, strip.Color( color.red, color.green, color.blue ) );
    strip.show();
}
