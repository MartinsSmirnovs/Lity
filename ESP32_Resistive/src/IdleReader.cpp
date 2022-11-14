#ifdef BUILD_ESP32

#include "IdleReader.h"

const std::vector<std::pair<gpio_num_t, uint8_t>> IdleReader::dataSelectPairs = {
    { GPIO_NUM_21, 0x1 },
    { GPIO_NUM_22, 0x2 },
    { GPIO_NUM_23, 0x4 }
};
const std::vector<gpio_num_t> IdleReader::commonInPins = { GPIO_NUM_33, GPIO_NUM_32, GPIO_NUM_35, GPIO_NUM_34 };

void IdleReader::setup() {
    for (const auto& pin : commonInPins) {
        pinMode(pin, INPUT);
    }

    for (const auto& pair : dataSelectPairs) {
        pinMode(pair.first, OUTPUT);
    }
}

void IdleReader::read(FieldsRaw& fields) {
    const auto commonInPinsCount = commonInPins.size();

    int counter = 0;

    for (int i = 0; i < commonInPinsCount; i++) {
        for (uint8_t j = 0; j < analogPinsPerChip; j++) {
            for (const auto& pair : dataSelectPairs) {
                digitalWrite(pair.first, j & pair.second);
            }

            if (counter < fieldsCount) {
                fields[counter] = analogRead(commonInPins[i]);
            } else {
                return;
            }
            counter++;
        }
    }
}

#endif
