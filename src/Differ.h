#pragma once

#include "LityConfig.h"
#include "Point.h"

class Differ {
public:
    static bool equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    static Point find(const Fields& fieldsLeft, const Fields& fieldsRight);
    static std::pair<int, uint16_t> diff(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);
    constexpr static int noDifference = -1;
};