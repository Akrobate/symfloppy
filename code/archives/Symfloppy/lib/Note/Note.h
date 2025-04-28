#ifndef Note_h
#define Note_h

#include <Arduino.h>

class Note {
    
    public:
        Note();
        Note(int note, unsigned int event_delta_ticks);
        void setNote(int note);
        int getNote();
        int getFrequency();
        boolean isNoteOn();
        void setNoteOff();
        void setEventDeltaMillis(unsigned int event_delta_ticks);
        unsigned int getEventDeltaMillis();
        int midiNoteToFrequency(int midi_note);

    private:
        int note;
        unsigned int event_delta_millis;

};

#endif