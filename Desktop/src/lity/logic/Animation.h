#pragma once

#include "Point.h"
#include "RGB.h"

class Animation {
public:
    // Value of Type is it's animation interval
    enum Type {
        appearance = 250, // fade
        payment    = 300 // blink
    };

    Animation(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    // Returns true if target value is not reached yet, false otherwise
    virtual bool update(unsigned long currentTime) = 0;

    const Point& getPoint() const;
    const RGB& getColor() const;

protected:
    const RGB colorTarget;
    RGB colorCurrent;

private:
    const Point point;
};