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


void LedInterface::update() {
    switch (this->animation) {
        case ANIMATION_BLINKING:
            this->animationBlinking();
            break;
        default:
            break;
    }
}


void LedInterface::animationBlinking() {
    unsigned long _millis = millis();
    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            for (int i = 0; i < 4; i++) {
                leds[i] = CHSV(
                    this->hue,
                    255,
                    map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255) % 256
                );
            }
        } else {
            for (int i = 0; i < 4; i++) {
                leds[i] = CHSV(
                    this->hue,
                    255,
                    (255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)) % 256
                );
            }
        }
        FastLED.show();

    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->resetAnimation();
        }
    }
}

void LedInterface::resetAnimation() {
    this->animation = ANIMATION_NO_ANIMATION;
    this->hue = 0;
    this->off();
}


void LedInterface::triggerBlinkingAnimation(uint8_t hue, unsigned long period_duration, bool loop_animation) {
    this->animation = ANIMATION_BLINKING;
    this->hue = hue;
    this->period_duration = period_duration;
    this->loop_animation = loop_animation;
    this->last_time = millis();
}
