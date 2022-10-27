#ifdef BUILD_ESP32

#include "LityManager.h"
#include "Converter.h"
#include "Differ.h"
#include "IdleReader.h"

void LityManager::setup() {
    pixelDriver.setup();
    IdleReader::setup();

    bool unfilled = true;
    do {
        // Initial reading and converting which is required for first time diff search
        IdleReader::read(rawFieldsPrevious);

        try {
            logic.populateFields(rawFieldsPrevious);
            unfilled = false;
        } catch (std::exception& exception) {
            Serial.println(exception.what());
        }

    } while (unfilled);
}

void LityManager::run() {
    IdleReader::read(rawFields);

    // Return if there is no diff between readings
    if (Differ::equal(rawFieldsPrevious, rawFields)) {
        return;
    }

    try {
        const auto& resultList = logic.process(rawFieldsPrevious, rawFields);

        for (const auto& result : resultList) {
            displayField(result.first, result.second);
        }
    } catch (std::exception& exception) {
        Serial.println(exception.what());
    }

    updatePreviousFields();
}

void LityManager::displayField(const Field& field, const Point& point) {
    const auto& rgb   = field.getColor();
    const int pointId = toId(point);
    const int stripId = Converter::toStripId(pointId);
    pixelDriver.setColor(stripId, rgb);
}

void LityManager::updatePreviousFields() {
    rawFieldsPrevious = rawFields;
}

int LityManager::toId(const Point& point) const {
    return Converter::toId(point, sideSize);
}

#endif
