// https://www.geeksforgeeks.org/generics-in-c/

#include <unity.h>
#include <iostream>

#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include <Note.h>
#include <DataStack.h>


void print_element(Note * el) {
    std::cout << "Note " << (int)el->getNote() << std::endl;
    std::cout << "DeltaTicks " << el->getEventDeltaTicks() << std::endl;
    std::cout << std::endl;
}


void test_something()
{
    Note * note;

    DataStack<Note> * data_stack = new DataStack<Note>();

    Note * note1 = new Note(1, 100);

    data_stack->push(note1);
    data_stack->push(new Note(2, 99));
    data_stack->push(new Note(3, 98));
    data_stack->push(new Note(4, 97));

    // delete data_stack;
    while(note = data_stack->getNext()) {
        print_element(note);
    }
    std::cout << "After declaration : " << data_stack->length() << std::endl;

    data_stack->removeAll(true);
    while(note = data_stack->getNext()) {
        print_element(note);
    }
    std::cout << "After removeAll : " << data_stack->length() << std::endl;

print_element(note1);
/*
    Note * note;
    while(note = data_stack->getNext()) {
        print_element(note);
    }

    while(note = data_stack->getNext()) {
        print_element(note);
    }

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;


    data_stack->resetCursor();


    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;

    print_element(data_stack->getCurrent());
    std::cout << "Next result:  " << (int)data_stack->next() << std::endl;


    std::cout << "data_stack length " << data_stack->length() << std::endl;
*/
    TEST_ASSERT_TRUE(true);
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_something);
    UNITY_END();
}