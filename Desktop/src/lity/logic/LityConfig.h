#pragma once

#include "Field.h"
#include <array>

constexpr int sideSize    = 12;
constexpr int fieldsCount = sideSize * sideSize;

using FieldsRaw = std::array<int, fieldsCount>;
using Fields    = std::array<std::array<Field, sideSize>, sideSize>;
