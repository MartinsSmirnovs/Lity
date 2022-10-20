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
    UNITY_END();
}
