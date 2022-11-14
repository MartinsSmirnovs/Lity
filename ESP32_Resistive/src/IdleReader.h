#pragma once

#include "LityConfig.h"
#include <Arduino.h>
#include <vector>

class IdleReader {
public:
    static void setup();
    static void read(FieldsRaw& fields);

private:
    // Pins from which data reading is happening
    static const std::vector<gpio_num_t> commonInPins;

    // Contains pairs of pin number and it's position for analog demultiplexer
    static const std::vector<std::pair<gpio_num_t, uint8_t>> dataSelectPairs;

    // How many pins per each analog demultiplexer chip
    constexpr static int analogPinsPerChip = 8;
};
