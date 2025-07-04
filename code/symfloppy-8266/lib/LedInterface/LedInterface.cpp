#include "LedInterface.h"

LedInterface::LedInterface() {
    
}

void LedInterface::init() {
    pinMode(PIN_NEOPIXEL_LED, OUTPUT);
    digitalWrite(PIN_NEOPIXEL_LED, LOW);
    for(int i = 0; i < NUM_LEDS; i++) {
        this->leds[i] = CRGB::Black;
    }
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(this->leds, NUM_LEDS);
    FastLED.clear();
    FastLED.delay(1);
    FastLED.show();
}

void LedInterface::onGreen() {
    for (int i = 0; i < NUM_LEDS; i++) {
        this->leds[i] = CRGB::Green;
    }
    this->show();
}

void LedInterface::onRed() {
    for (int i = 0; i < NUM_LEDS; i++) {
        this->leds[i] = CRGB::Red;
    }
    this->show();
}

void LedInterface::off() {
    for (int i = 0; i < NUM_LEDS; i++) {
        this->leds[i] = CRGB::Black;
    }
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
        case ANIMATION_FIXED_COLOR:
            this->animationFixedColor();
            break;
        default:
            break;
    }
}


void LedInterface::animationFixedColor() {
    unsigned long _millis = millis();
    if (_millis < this->last_time + this->period_duration) {
        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CHSV(
                this->hue,
                255,
                map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255) % 256
            );
        }
        this->show();
    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->resetAnimation();
        }
    }
}



void LedInterface::animationBlinking() {
    unsigned long _millis = millis();
    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CHSV(
                    this->hue,
                    255,
                    map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255) % 256
                );
            }
        } else {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CHSV(
                    this->hue,
                    255,
                    (255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)) % 256
                );
            }
        }
        this->show();

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


void LedInterface::triggerFixedColor(uint8_t hue) {
    this->animation = ANIMATION_FIXED_COLOR;
    this->hue = hue;
    this->period_duration = 500; // 2 seconds
    this->loop_animation = true;
    this->last_time = millis();
}


void LedInterface::triggerFixedColorGreen() {
    this->triggerFixedColor(128);
}


void LedInterface::triggerFixedColorRed() {
    this->triggerFixedColor(0);
}