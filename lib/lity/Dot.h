#pragma once

#include "Figure.h"

class Dot : public Figure {
public:
    bool find(const Fields& fields, const FieldPoint& fieldPoint) const override;
    AnimationList apply(Fields& fields, const FieldPoint& fieldPoint) const override;
};
