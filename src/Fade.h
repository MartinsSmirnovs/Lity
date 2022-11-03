#pragma once

#include "Animation.h"
#include "Waiter.h"
#include <array>
#include <utility>

class Fade : public Animation {
public:
    Fade(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(unsigned long timeCurrent) override;

private:
    enum Direction {
        down = 0,
        up,
        stop
    };

    void setup();
    uint8_t calculate(int time, Direction direction) const;

    bool firstTime = true;

    unsigned long timeInitial = 0;

    Direction direction = stop;

    Waiter waiter;

    using ColorDirectionPair = std::pair<uint8_t&, Direction>;
    std::array<ColorDirectionPair, RGB::colorsInPixel> colorDirectionList{ ColorDirectionPair{ colorCurrent.red, stop },
                                                                           ColorDirectionPair{ colorCurrent.green, stop },
                                                                           ColorDirectionPair{ colorCurrent.blue, stop } };

    const std::array<uint8_t, RGB::colorsInPixel> colorTargetList{ colorTarget.red,
                                                                   colorTarget.green,
                                                                   colorTarget.blue };
};