#ifndef FrequencyGenerator_h
#define FrequencyGenerator_h

#include <Arduino.h>

class FrequencyGenerator {
    
    public:
        FrequencyGenerator();
        FrequencyGenerator(int pin);
        
        void setFrequency(int frequency);
        void setPin(int pin);

        void start();
        void stop();
        void update();

        unsigned long getPulseCount();
        void resetPulseCount();

    private:
        void init();

        boolean running;
        int pin;
        int frequency;
        unsigned long period_duration_micros;
        unsigned long time_micros;
        unsigned long pulse_count;

        boolean pin_state;


};

#endif