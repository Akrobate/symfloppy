#ifndef Note_h
#define Note_h

#include <Arduino.h>

class Note {
    
    public:
        Note();
        Note(int note, unsigned int event_delta_ticks);
        void setNote(int note);
        int getNote();
        void setEventDeltaTicks(unsigned int event_delta_ticks);
        unsigned int getEventDeltaTicks();

    private:
        int note;
        unsigned int event_delta_ticks;

};

#endif