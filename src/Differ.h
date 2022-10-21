#pragma once

#include "Coord.h"
#include "LityConfig.h"

class Differ {
public:
    static bool equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    static Coord find(const Fields& fieldsLeft, const Fields& fieldsRight);
};