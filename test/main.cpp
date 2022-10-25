#ifdef BUILD_TESTS

#include "Tests.h"
#include <unity.h>

void setUp(void) {
}

void tearDown(void) {
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(testDiffer_diff);
    RUN_TEST(testDiffer_find);
    RUN_TEST(testPoint_isEmpty);
    RUN_TEST(testConverter_toId);
    RUN_TEST(testField_constructor);
    UNITY_END();
}

#endif
