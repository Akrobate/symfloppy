#include "LedInterface.h"

LedInterface::LedInterface() {
    
}

void LedInterface::init() {
    pinMode(PIN_NEOPIXEL_LED, OUTPUT);
    digitalWrite(PIN_NEOPIXEL_LED, LOW);
    for(int i = 0; i < 3; i++) {
        this->leds[i] = CRGB::Black;
    }
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(this->leds, 3);
    FastLED.clear();
    FastLED.delay(1);
    FastLED.show();
}

void LedInterface::onGreen() {
    this->leds[0] = CRGB::Green;
    this->show();
}

void LedInterface::onRed() {
    this->leds[0] = CRGB::Red;
    this->show();
}

void LedInterface::off() {
    this->leds[0] = CRGB::Black;
    this->show();
}

void LedInterface::show() {
    FastLED.delay(1);
    FastLED.show();
}