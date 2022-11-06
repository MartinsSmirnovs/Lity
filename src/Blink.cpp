#include "Blink.h"

Blink::Blink(const RGB& colorCurrent, const RGB& colorTarget, const Point& point)
: Animation(colorCurrent, colorTarget, point),
  colorHigh(colorCurrent),
  waiter(Animation::payment) {
}

bool Blink::update(unsigned long currentTime) {
    if (blinkCounter >= timesToBlink) {
        return false;
    }

    if (waiter.isReady(currentTime)) {
        blinkCounter++;

        if (colorCurrent == colorHigh) {
            colorCurrent = colorTarget;
            return true;
        }

        if (colorCurrent == colorTarget) {
            colorCurrent = colorHigh;
            return true;
        }
    }
    return true;
}
