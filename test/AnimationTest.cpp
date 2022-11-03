#ifdef BUILD_TESTS

#include "Blink.h"
#include "Fade.h"
#include <unity.h>

void testFade_Update() {
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

void testBlink_Update() {
    static_assert(Animation::payment == 300);

    const RGB turquoise(0, 255, 255);
    const RGB black;

    Blink blink(turquoise, black, Point());

    TEST_ASSERT_TRUE(blink.update(300));

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT(0, color.red);
        TEST_ASSERT_EQUAL_INT(0, color.green);
        TEST_ASSERT_EQUAL_INT(0, color.blue);
    }

    TEST_ASSERT_TRUE(blink.update(600));

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT(0, color.red);
        TEST_ASSERT_EQUAL_INT(255, color.green);
        TEST_ASSERT_EQUAL_INT(255, color.blue);
    }

    TEST_ASSERT_TRUE(blink.update(900));
    TEST_ASSERT_TRUE(blink.update(1200));
    TEST_ASSERT_TRUE(blink.update(1500));

    TEST_ASSERT_FALSE(blink.update(1800));

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT(0, color.red);
        TEST_ASSERT_EQUAL_INT(0, color.green);
        TEST_ASSERT_EQUAL_INT(0, color.blue);
    }
}

#endif
