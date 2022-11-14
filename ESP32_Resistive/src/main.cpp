#ifdef BUILD_ESP32
#include "LityManager.h"

LityManager manager;

void setup() {
    Serial.begin(115200);
    manager.setup();
}

void loop() {
    manager.run();
    delay(10);
}

#endif
