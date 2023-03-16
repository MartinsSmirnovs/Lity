#pragma once

#include "Figure.h"
#include "FigureDescription.h"

class Arrowhead : public Figure {
public:
    Arrowhead();
    bool find(const Fields& fields, const FieldPoint& fieldPoint) override;
    AnimationList apply(Fields& fields, const FieldPoint& fieldPoint) override;

private:
    using Direction = FigureDescription::Direction;

    bool onlyOneFound        = false;
    Direction foundDirection = Direction::top;

    void searchByRotation(Direction direction, const Fields& fields, const FieldPoint& fieldPoint);
};
