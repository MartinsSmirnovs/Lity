#pragma once

#include "Field.h"
#include "Point.h"
#include <array>
#include <utility>

#ifdef BUILD_ESP32
constexpr int sideSize = 5;
#elif BUILD_TESTS
constexpr int sideSize = 5;
#else
constexpr int sideSize = 10;
#endif

constexpr int fieldsCount = sideSize * sideSize;

using FieldsRaw = std::array< int, fieldsCount >;
using Fields = std::array< std::array< Field, sideSize >, sideSize >;
using FieldPoint = std::pair< Field, Point >;
