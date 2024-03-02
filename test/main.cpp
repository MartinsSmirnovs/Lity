#include "Tests.h"
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

int main( int argc, char** argv )
{
    UNITY_BEGIN();
    // RUN_TEST(testDiffer_diff);
    // RUN_TEST(testDiffer_areAllElementsSame);
    // RUN_TEST(testDiffer_equal);
    // RUN_TEST(testPoint_isEmpty);
    // RUN_TEST(testConverter_toId);
    // RUN_TEST(testField_constructor);
    // RUN_TEST(testField_getColor);
    // RUN_TEST(testField_upgrade);
    // RUN_TEST(testField_operatorEquals);
    // RUN_TEST(testPoint_Constructor);
    // RUN_TEST(testPoint_isEmpty);
    // RUN_TEST(testPoint_hasNegative);
    // RUN_TEST(testPoint_operatorPlus);
    // RUN_TEST(testPoint_OperatorEquals);
    // RUN_TEST(testPoint_ConstructorEqualsNot);
    // RUN_TEST(testFade_Update);
    // RUN_TEST(testBlink_Update);
    RUN_TEST( testCross_find );
    RUN_TEST( testCross_apply );
    RUN_TEST( testSquare_find );
    RUN_TEST( testSquare_apply );
    UNITY_END();
}
