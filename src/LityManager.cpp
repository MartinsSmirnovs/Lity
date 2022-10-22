#ifdef BUILD_ESP32

#include "LityManager.h"
#include "Converter.h"
#include "Differ.h"
#include "Field.h"
#include "IdleReader.h"

void LityManager::setup() {
    pixelDriver.setup();
    IdleReader::setup();

    // Initial reading and converting which is required for first time diff search
    IdleReader::read(rawFieldsPrevious);
    Converter::toFields(rawFieldsPrevious, fieldsPrevious);
}

void LityManager::run() {
    IdleReader::read(rawFields);

    // Return if there is no diff between readings
    if (Differ::equal(rawFieldsPrevious, rawFields)) {
        return;
    }

    Converter::toFields(rawFields, fields);
    const auto coord = Differ::find(fieldsPrevious, fields);

    Field field;
    try {
        field = Field(fields[coord.y][coord.x]);
    } catch (const std::exception& exception) {
        updatePreviousFields();
        return;
    }

    const RGB rgb = field.getColor();

    const int coordId = toId(coord);
    const int stripId = Converter::toStripId(coordId);
    pixelDriver.setColor(stripId, rgb);

    updatePreviousFields();
}

void LityManager::updatePreviousFields() {
    rawFieldsPrevious = rawFields;
    fieldsPrevious    = fields;
}

int LityManager::toId(const Coord& coord) const {
    return Converter::toId(coord, sideSize);
}

#endif