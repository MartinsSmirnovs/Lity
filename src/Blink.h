#pragma once

#include "Animation.h"
#include "Waiter.h"

class Blink : public Animation {
public:
    Blink(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(int currentTime) override;

private:
    Waiter waiter;
};