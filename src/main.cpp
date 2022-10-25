#ifdef BUILD_ESP32
#include "LityManager.h"

LityManager manager;

void setup() {
    manager.setup();
    Serial.begin(115200);
}

// void rainbow(int);

// void display(const Fields& v) {
//     int counter = 0;
//     for (const auto& i : v) {
//         for (const auto& j : i) {
//             if (counter < 10) {
//                 Serial.print(" ");
//             }
//             Serial.print(counter);
//             Serial.print(".");
//             Serial.print(j);
//             Serial.print(" ");
//             counter++;
//         }
//         Serial.println();
//     }

//     Serial.println();
//     Serial.println();
//     Serial.println();
// }

void loop() {
    manager.run();
    delay(10);
}


// void rainbow(int wait) {
//     for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
//         for (int i = 0; i < strip.numPixels(); i++) {
//             int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//             strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//         }
//         strip.show();
//         delay(wait);
//     }
// }
#endif
