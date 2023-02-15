#pragma once

#include "Field.h"
#include <array>

#ifdef BUILD_ESP32
constexpr int sideSize = 5;
#else
constexpr int sideSize = 12;
#endif

constexpr int fieldsCount = sideSize * sideSize;

using FieldsRaw = std::array<int, fieldsCount>;
using Fields    = std::array<std::array<Field, sideSize>, sideSize>;
