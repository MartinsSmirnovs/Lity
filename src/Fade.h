#pragma once

#include "Animation.h"
#include "Waiter.h"

class Fade : public Animation {
public:
    Fade(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(int currentTime) override;

private:
    Waiter waiter;
};