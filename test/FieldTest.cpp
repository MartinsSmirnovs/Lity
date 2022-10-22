#ifdef BUILD_TESTS

#include "Field.h"
#include <unity.h>

void testField_constructor() {
    static_assert(Field::green == 2457);
    static_assert(Field::blue == 738);

    // Lower bound exception test
    {
        try {
            const Field field(4095);
        } catch (const std::exception& exception) {
            TEST_ASSERT_EQUAL_STRING("Lower bound for value 4095 could not be found!", exception.what());
        }
    }

    // Blue value out of range because too big test
    {
        try {
            const Field field(950);
        } catch (const std::exception& exception) {
            TEST_ASSERT_EQUAL_STRING("Value 950 is out of range!", exception.what());
        }
    }

    // Blue value out of range because too small test
    {
        try {
            const Field field(400);
        } catch (const std::exception& exception) {
            TEST_ASSERT_EQUAL_STRING("Value 400 is out of range!", exception.what());
        }
    }

    // Slightly bigger but in range white value test
    {
        try {
            const Field field(2557);

            TEST_ASSERT_EQUAL_INT(Field::green, field.getType());

            const auto rgb = field.getColor();
            TEST_ASSERT_EQUAL_INT(0, rgb.red);
            TEST_ASSERT_EQUAL_INT(255, rgb.green);
            TEST_ASSERT_EQUAL_INT(0, rgb.blue);

        } catch (const std::exception& exception) {
            TEST_FAIL_MESSAGE(exception.what());
        }
    }

    // Slightly smaller but in range white value test
    {
        try {
            const Field field(2357);
            TEST_ASSERT_EQUAL_INT(Field::green, field.getType());

            const auto rgb = field.getColor();
            TEST_ASSERT_EQUAL_INT(0, rgb.red);
            TEST_ASSERT_EQUAL_INT(255, rgb.green);
            TEST_ASSERT_EQUAL_INT(0, rgb.blue);

        } catch (const std::exception& exception) {
            TEST_FAIL_MESSAGE(exception.what());
        }
    }
}

#endif
