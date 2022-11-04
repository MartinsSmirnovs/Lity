#ifdef BUILD_ESP32

#include "LityManager.h"
#include "Converter.h"
#include "Differ.h"
#include "IdleReader.h"

LityManager::LityManager()
: waiter(debounceInterval) {
}

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

    // Debouncing
    if (!waiter.isReady(millis())) {
        return;
    }

    try {
        auto animations = logic.process(rawFieldsPrevious, rawFields);
        doAnimations(animations);

    } catch (std::exception& exception) {
        Serial.println(exception.what());
    }

    updatePreviousFields();
}

void LityManager::doAnimations(LityLogic::AnimationList& animationList) {
    while (animationList.size()) {
        for (int i = 0; i < animationList.size(); i++) {
            auto& animation = animationList[i];

            const bool updated = animation->update(millis());

            if (!updated) {
                animationList.erase(animationList.begin() + i);
                i--;
                continue;
            }

            const auto& color = animation->getColor();
            const auto& point = animation->getPoint();

            displayColor(color, point);
        }
    }
}

void LityManager::displayColor(const RGB& color, const Point& point) {
    const int pointId = toId(point);
    const int stripId = Converter::toStripId(pointId);
    pixelDriver.setColor(stripId, color);
}

void LityManager::updatePreviousFields() {
    rawFieldsPrevious = rawFields;
}

int LityManager::toId(const Point& point) const {
    return Converter::toId(point, sideSize);
}

#endif
