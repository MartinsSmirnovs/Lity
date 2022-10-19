#include "IdleReader.h"

void IdleReader::setup() const {
    for (const auto& pin : commonInPins) {
        pinMode(pin, INPUT);
    }

    for (const auto& pair : dataSelectPairs) {
        pinMode(pair.first, OUTPUT);
    }
}

void IdleReader::read() {
    const auto commonInPinsCount = commonInPins.size();

    int counter = 0;

    for (int i = 0; i < commonInPinsCount; i++) {
        for (uint8_t j = 0; j < analogPinsPerChip; j++) {
            for (const auto& pair : dataSelectPairs) {
                digitalWrite(pair.first, j & pair.second);
            }

            if (counter < fieldsCount) {
                rawFields[counter] = analogRead(commonInPins[i]);
            } else {
                return;
            }
            counter++;
        }
    }
}

const FieldsRaw& IdleReader::getRawFields() const {
    return rawFields;
}
