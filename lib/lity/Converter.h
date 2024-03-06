#pragma once

#include "LityConfig.h"
#include "Point.h"

namespace Converter
{
    void toFields( const FieldsRaw& rawFields, Fields& fields );
    int toId( const Point& point, int rows );
    Point toFieldId( int rawId );
}