#ifdef BUILD_TESTS

#include "Converter.h"
#include <unity.h>

void testConverter_toId() {
    {
        const Coord coord = { 1, 2 };
        const int result  = Converter::toId(coord, 5);
        TEST_ASSERT_EQUAL_INT(7, result);
    }

    {
        const Coord coord = { 0, 0 };
        const int result  = Converter::toId(coord, 5);
        TEST_ASSERT_EQUAL_INT(0, result);
    }

    {
        const Coord coord = { 4, 4 };
        const int result  = Converter::toId(coord, 5);
        TEST_ASSERT_EQUAL_INT(24, result);
    }
}

#endif
