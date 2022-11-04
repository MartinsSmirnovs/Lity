#pragma once
#ifdef BUILD_ESP32

#include "LityConfig.h"
#include "LityLogic.h"
#include "PixelDriver.h"
#include "Waiter.h"

class LityManager {
public:
    LityManager();

    void setup();
    void run();

private:
    PixelDriver pixelDriver;
    LityLogic logic;

    Waiter waiter;
    constexpr static int debounceInterval = 400;

    FieldsRaw rawFields;
    FieldsRaw rawFieldsPrevious;

    void updatePreviousFields();
    void displayColor(const RGB& color, const Point& point);

    void doAnimations(LityLogic::AnimationList& animationList);

    int toId(const Point& point) const;
};

#endif
