#pragma once

#include "Animation.h"
#include "Field.h"
#include "Point.h"
#include <vector>

class FigureDescription {
    using Building = Field::Building;

public:
    Point center;
    std::vector<std::vector<Field::Type>> colorMask;
    std::vector<std::vector<Field::Type>> paymentMask;
    std::vector<std::vector<Building>> buildingMask;
    std::vector<std::vector<bool>> upgradeMask;
    std::vector<std::vector<Animation::Type>> animationMask;

    enum class Direction {
        top,
        left,
        bottom,
        right
    };

    enum class Axis {
        x,
        y,
        both
    };

    template <typename TwoDimensionalVector>
    void flip(TwoDimensionalVector& mask, Point& point, Axis axis);
    void flip(Direction direction);
    void flip(Axis axis);
};
