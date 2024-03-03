#include "LityManager.h"
#include <Arduino.h>

LityManager manager;

void setup()
{
    manager.setup();
}

void loop()
{
    manager.run();
    delay( 10 );
}
