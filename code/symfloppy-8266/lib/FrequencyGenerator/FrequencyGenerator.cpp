#include "FrequencyGenerator.h"

FrequencyGenerator::FrequencyGenerator() {
    this->init();
}

FrequencyGenerator::FrequencyGenerator(int pin) {
    this->setPin(pin);
    this->init();
}

void FrequencyGenerator::init() {
    this->running = false;
    this->time_micros = micros();
    this->pulse_count = 0;
    this->pin_state = false;
}

void FrequencyGenerator::setFrequency(int frequency) {
    this->frequency = frequency;
    this->period_duration_micros = 1000000 / frequency;
}

void FrequencyGenerator::setPin(int pin) {
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void FrequencyGenerator::start() {
    this->time_micros = micros();
    this->running = true;
}

void FrequencyGenerator::stop() {
    this->running = false;
    digitalWrite(this->pin, LOW);
}

void FrequencyGenerator::update() {
    if (!this->running) {
        return;
    }

    if (micros() > (this->time_micros + (this->period_duration_micros / 2))) {
        this->time_micros = micros();
        this->pin_state = !this->pin_state;
        digitalWrite(this->pin, this->pin_state ? HIGH : LOW);
        if (this->pin_state) {
            this->pulse_count = this->pulse_count + 1;
        }
    }
}

unsigned long FrequencyGenerator::getPulseCount() {
    return this->pulse_count;
}

void FrequencyGenerator::resetPulseCount() {
    this->pulse_count = 0;
}
