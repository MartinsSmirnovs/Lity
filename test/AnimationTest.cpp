#ifdef BUILD_TESTS

#include "Fade.h"
#include <unity.h>

void testFade_Update() {
    {
        static_assert(Animation::appearance == 10);

        const RGB red(255, 0, 0);
        const RGB black;

        Fade fade(red, black, Point());

        // Performs setup
        TEST_ASSERT_TRUE(fade.update(100));

        fade.update(100 + Animation::appearance * 10);
        fade.update(100 + Animation::appearance * 15);

        // Check if the value is still falling
        TEST_ASSERT_TRUE(fade.update(100 + Animation::appearance * 20));

        {
            const auto& color = fade.getColor();

            TEST_ASSERT_EQUAL_INT(166, color.red);
            TEST_ASSERT_EQUAL_INT(0, color.green);
            TEST_ASSERT_EQUAL_INT(0, color.blue);
        }

        // Fade should drop to it's lowest value here
        TEST_ASSERT_TRUE(fade.update(100 + 510));

        // Fade should stop dropping after getting to it's lowest value
        TEST_ASSERT_FALSE(fade.update(100 + 530));

        {
            const auto& color = fade.getColor();

            TEST_ASSERT_EQUAL_INT(0, color.red);
            TEST_ASSERT_EQUAL_INT(0, color.green);
            TEST_ASSERT_EQUAL_INT(0, color.blue);
        }
    }
}

#endif
