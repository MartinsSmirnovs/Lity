#ifdef BUILD_TESTS

#include "Converter.h"
#include <unity.h>

void testConverter_toId() {
    {
        const Point point = { 1, 2 };
        const int result  = Converter::toId(point, 5);
        TEST_ASSERT_EQUAL_INT(7, result);
    }

    {
        const Point point = { 0, 0 };
        const int result  = Converter::toId(point, 5);
        TEST_ASSERT_EQUAL_INT(0, result);
    }

    {
        const Point point = { 4, 4 };
        const int result  = Converter::toId(point, 5);
        TEST_ASSERT_EQUAL_INT(24, result);
    }
}

#endif
