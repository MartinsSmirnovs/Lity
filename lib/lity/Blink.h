#pragma once

#include "Animation.h"
#include "Waiter.h"

class Blink : public Animation {
public:
    Blink(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(unsigned long currentTime) override;

private:
    Waiter waiter;

    constexpr static int timesToBlink = 5;
    static_assert(timesToBlink % 2 != 0);

    int blinkCounter = 0;

    const RGB colorHigh; // and colorTarget is colorLow
};