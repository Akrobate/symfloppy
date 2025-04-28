// https://www.geeksforgeeks.org/generics-in-c/

#include <unity.h>
#include <iostream>

#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Note.h>


void print_element(Note * el) {
    std::cout << "Note " << (int)el->getNote() << std::endl;
    std::cout << "DeltaTicks " << el->getEventDeltaTicks() << std::endl;
    std::cout << std::endl;
}


void test_something()
{
    Note * note;
    TEST_ASSERT_TRUE(true);
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_something);
    UNITY_END();
}