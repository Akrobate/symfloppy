#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <configurations.h>

#define PIN_NEOPIXEL_LED    PIN_NEOPIXEL // PIN_D6


class LedInterface {

    private:
        CRGB leds[3];

    public:
        LedInterface();
        void init();

        void onGreen();
        void onRed();

        void off();
        void show();

};
