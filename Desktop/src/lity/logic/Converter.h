#pragma once

#include "LityConfig.h"
#include "Point.h"

class Converter {
public:
    static void toFields(const FieldsRaw& rawFields, Fields& fields);
    static int toStripId(int id);
    static int toId(const Point& point, int rows);
    static Point toFieldId(int rawId);
};