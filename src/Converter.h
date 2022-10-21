#pragma once

#include "Coord.h"
#include "LityConfig.h"

class Converter {
public:
    static void toFields(const FieldsRaw& rawFields, Fields& fields);
    static int toStripId(int id);
    static int toId(const Coord& coord, int rows);
};