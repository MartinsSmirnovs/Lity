#pragma once

#include "Figure.h"
#include "FigureDescription.h"

class Arrowhead : public Figure {
    using Direction = FigureDescription::Direction;
public:
    Arrowhead();
    Arrowhead(Direction direction);
};
