#ifndef ButtonsInterface_h
#define ButtonsInterface_h

#include <Arduino.h>
#include <Toggle.h>
#include <configurations.h>

class ButtonsInterface {

    private:
        unsigned int PIN_BTN_LEFT = PIN_BUTTON_LEFT;
        unsigned int PIN_BTN_MIDDLE = PIN_BUTTON_MIDDLE;
        unsigned int PIN_BTN_RIGHT = PIN_BUTTON_RIGHT;


    public:

        Toggle * button_left = nullptr;
        Toggle * button_middle = nullptr;
        Toggle * button_right = nullptr;

        ButtonsInterface();
    
        void init();
        void update();

        bool onRight();
        bool onLeft();
        bool onMiddle();

};

#endif