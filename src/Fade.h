#pragma once

#include "Animation.h"
#include "Waiter.h"
#include <array>
#include <utility>

class Fade : public Animation {
public:
    Fade(const RGB& colorCurrent, const RGB& colorTarget, const Point& point);

    bool update(unsigned long currentTime) override;

private:
    Waiter waiter;

    bool firstTime = true;

    unsigned long previousTime = 0;

    void setup();

    enum Direction {
        down = 0,
        up,
        stop
    };
    bool direction = false;


    using ColorDirectionPair = std::pair<uint8_t&, Direction>;
    std::array<ColorDirectionPair, RGB::colorsInPixel> colorDirectionList{ ColorDirectionPair{ colorCurrent.red, stop },
                                                                           ColorDirectionPair{ colorCurrent.green, stop },
                                                                           ColorDirectionPair{ colorCurrent.blue, stop } };

    const std::array<uint8_t, RGB::colorsInPixel> colorTargetList{ colorTarget.red,
                                                                   colorTarget.green,
                                                                   colorTarget.blue };

    uint8_t calculate(int time, Direction direction) const;
};