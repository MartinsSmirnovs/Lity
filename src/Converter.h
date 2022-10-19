#pragma once

#include "LityConfig.h"

class Converter
{
public:
    static Fields toFields( const FieldsRaw& rawFields );
    static int toStripId(int id);
};