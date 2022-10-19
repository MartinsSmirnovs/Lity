#pragma once

#include "LityConfig.h"
#include <Arduino.h>
#include <vector>

class IdleReader {
public:
    void setup() const;

    void read();
    const FieldsRaw& getRawFields() const;

private:
    FieldsRaw rawFields;

    const std::vector<gpio_num_t> commonInPins = { GPIO_NUM_33, GPIO_NUM_32, GPIO_NUM_35, GPIO_NUM_34 };

    // Contains pairs of pin number and it's position for analog demultiplexer
    const std::vector<std::pair<gpio_num_t, uint8_t>> dataSelectPairs = { { GPIO_NUM_21, 0x1 }, { GPIO_NUM_22, 0x2 }, { GPIO_NUM_23, 0x4 } };

    // How many pins per each analog demultiplexer chip
    constexpr static int analogPinsPerChip = 8;
};