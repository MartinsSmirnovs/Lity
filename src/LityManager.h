#pragma once
#ifdef BUILD_ESP32

#include "Coord.h"
#include "LityConfig.h"
#include "PixelDriver.h"

class LityManager {
public:
    void setup();
    void run();

private:
    PixelDriver pixelDriver;

    FieldsRaw rawFields;
    FieldsRaw rawFieldsPrevious;

    Fields fields;
    Fields fieldsPrevious;

    int toId(const Coord& coord) const;
};

#endif
