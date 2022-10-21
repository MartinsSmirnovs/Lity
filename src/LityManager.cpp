#ifdef BUILD_ESP32

#include "LityManager.h"
#include "Converter.h"
#include "Differ.h"
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

    const RGB rgb = { 255, 0, 0 };

    const int coordId = toId(coord);
    const int stripId = Converter::toStripId(coordId);
    pixelDriver.setColor(stripId, rgb);

    rawFieldsPrevious = rawFields;
    fieldsPrevious    = fields;
}

int LityManager::toId(const Coord& coord) const {
    return Converter::toId(coord, sideSize);
}

#endif