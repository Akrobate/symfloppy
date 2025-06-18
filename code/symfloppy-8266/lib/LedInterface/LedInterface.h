#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <configurations.h>

#define PIN_NEOPIXEL_LED    PIN_NEOPIXEL // PIN_D6
#define NUM_LEDS          3

class LedInterface {

    private:
        CRGB leds[NUM_LEDS];

        unsigned long last_time = 0;
        unsigned int period_duration = 1000;
        boolean loop_animation = false;

        int animation;
        void animationBlinking();
        int hue = 0;

    public:
        static constexpr int ANIMATION_NO_ANIMATION = 0;
        static constexpr int ANIMATION_BLINKING = 1;

        LedInterface();
        void init();

        void onGreen();
        void onRed();

        void off();
        void show();

        void update();
        void resetAnimation();
        void triggerBlinkingAnimation(uint8_t hue, unsigned long period_duration, bool loop_animation = false);

};
