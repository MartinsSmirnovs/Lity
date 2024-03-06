#pragma once

#include "LityConfig.h"

namespace IdleReader
{
    void setup();
    void read( FieldsRaw& fields );
    void readUndebounced( FieldsRaw& fields );
}
