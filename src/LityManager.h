#pragma once
#ifdef BUILD_ESP32

#include "LityConfig.h"
#include "LityLogic.h"
#include "PixelDriver.h"

class LityManager {
public:
    void setup();
    void run();

private:
    PixelDriver pixelDriver;
    LityLogic logic;

    FieldsRaw rawFields;
    FieldsRaw rawFieldsPrevious;

    void updatePreviousFields();
    void displayField(const Field& field, const Point& point);

    int toId(const Point& point) const;
};

#endif
