#include "IdleReader.h"

void IdleReader::setup() const {
    for (const auto& pin : commonInPins) {
        pinMode(pin, INPUT);
    }

    for (const auto& pair : dataSelectPairs) {
        pinMode(pair.first, OUTPUT);
    }
}

auto IdleReader::read() -> const FieldsArray& {
    const auto commonInPinsCount = commonInPins.size();

    for (int i = 0; i < commonInPinsCount; i++) {
        for (uint8_t j = 0; j < analogPinsPerChip; j++) {
            for (const auto& pair : dataSelectPairs) {
                digitalWrite(pair.first, j & pair.second);
            }

            const int cellId = i * commonInPinsCount + j;
            if (cellId < fieldsCount) {
                rawFields[cellId] = analogRead(commonInPins[i]);
            }
        }
    }

    return rawFields;
}

auto IdleReader::getRawArray() const -> const FieldsArray& {
    return rawFields;
}
