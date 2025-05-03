#include "ButtonsInterface.h"


ButtonsInterface::ButtonsInterface() {
    this->init();
}


void ButtonsInterface::init() {

    pinMode(this->PIN_BTN_LEFT, INPUT_PULLUP);
    pinMode(this->PIN_BTN_MIDDLE, INPUT_PULLUP);
    pinMode(this->PIN_BTN_RIGHT, INPUT_PULLUP);
    
    this->button_left = new Toggle(this->PIN_BTN_LEFT);
    this->button_middle = new Toggle(this->PIN_BTN_MIDDLE);
    this->button_right = new Toggle(this->PIN_BTN_RIGHT);
}


void ButtonsInterface::update() {

    this->button_left->poll();
    this->button_middle->poll();
    this->button_right->poll();

    /*
    // DEBUG code
    if (this->button_left->onPress()) {
        Serial.println("button_left pressed");
    }
    if (this->button_middle->onPress()) {
        Serial.println("button_middle pressed");
    }
    if (this->button_right->onPress()) {
        Serial.println("button_right pressed");
    }
    */
}


bool ButtonsInterface::onLeft() {
    return this->button_left->onPress();
}

bool ButtonsInterface::onMiddle() {
    return this->button_middle->onPress();
}

bool ButtonsInterface::onRight() {
    return this->button_right->onPress();
}
