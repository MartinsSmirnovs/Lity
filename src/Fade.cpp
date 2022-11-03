#include "Fade.h"
#include <cmath>
#include <limits>

Fade::Fade(const RGB& colorCurrent, const RGB& colorTarget, const Point& point)
: Animation(colorCurrent, colorTarget, point),
  waiter(Animation::appearance) {
}

bool Fade::update(unsigned long timeCurrent) {
    // First time setup
    if (firstTime) {
        setup();
        waiter.isReady(timeCurrent);

        timeInitial = timeCurrent;
        firstTime   = false;

        return true;
    }

    // If target color is reached, cannot update anymore
    if (colorCurrent == colorTarget) {
        return false;
    }

    // Execute only if required timeout has passed
    if (waiter.isReady(timeCurrent)) {
        for (auto& pair : colorDirectionList) {
            auto& color          = pair.first;
            const auto direction = pair.second;

            if (direction == stop) {
                continue;
            }

            const auto time   = timeCurrent - timeInitial;
            const auto result = calculate(time, direction);

            if (direction == down && result > color) {
                color = std::numeric_limits<uint8_t>::min();
            } else if (direction == up && result < color) {
                color = std::numeric_limits<uint8_t>::max();
            } else {
                color = result;
            }
        }
    }

    return true;
}

void Fade::setup() {
    // Decide which direction each color of RGB will go
    for (int i = 0; i < colorDirectionList.size(); i++) {
        const uint8_t color       = colorDirectionList[i].first;
        const uint8_t colorTarget = colorTargetList[i];

        if (color > colorTarget) {
            colorDirectionList[i].second = down;
        } else if (color < colorTarget) {
            colorDirectionList[i].second = up;
        } else {
            colorDirectionList[i].second = stop;
        }
    }
}

uint8_t Fade::calculate(int time, Direction direction) const {
    constexpr float yOffset   = std::numeric_limits<uint8_t>::max() / 2.0f;
    constexpr float amplitude = std::numeric_limits<uint8_t>::max() / 2.0f;

    constexpr auto pi = M_PI;

    constexpr float range = Animation::appearance * 50;

    const uint8_t result = yOffset + amplitude * std::cos(pi / range * time + pi * direction);

    return result;
}