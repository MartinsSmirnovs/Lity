#include "Fade.h"

Fade::Fade(const RGB& colorCurrent, const RGB& colorTarget, const Point& point)
: Animation(colorCurrent, colorTarget, point),
  waiter(Animation::appearance) {
}

bool Fade::update(int currentTime) {
    bool status = true;

    if (waiter.isReady(currentTime)) {
        // Cannot update if target color is reached
        if (colorTarget == colorCurrent) {
            return false;
        }

        // Perform color transformations

    } else {
        return true;
    }
}
