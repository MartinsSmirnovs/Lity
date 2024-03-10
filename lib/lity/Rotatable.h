#pragma once

#include "Figure.h"
#include "FigureDescription.h"

class Rotatable : public Figure
{
public:
    bool find( const Fields& fields, const FieldPoint& fieldPoint ) override;
    AnimationList apply( Fields& fields, const FieldPoint& fieldPoint ) override;

private:
    using Direction = FigureDescription::Direction;
    void searchByRotation( Direction direction, const Fields& fields, const FieldPoint& fieldPoint );

    bool onlyOneFound = false;
    Direction foundDirection = Direction::top;
};
