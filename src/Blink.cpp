#include "Blink.h"

Blink::Blink(const RGB& colorCurrent, const RGB& colorTarget, const Point& point)
: Animation(colorCurrent, colorTarget, point),
  waiter(Animation::payment) {
}

bool Blink::update(int currentTime) {
    return true;
}
