#pragma once

#include <array>
constexpr int sideSize    = 5;
constexpr int fieldsCount = sideSize * sideSize;

using FieldsRaw = std::array<int, fieldsCount>;
using Fields    = std::array<std::array<int, sideSize>, sideSize>;
