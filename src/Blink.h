#pragma once

#include "Animation.h"
#include "Waiter.h"

class Blink : public Animation {
public:
    Blink(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(unsigned long currentTime) override;

private:
    Waiter waiter;
};