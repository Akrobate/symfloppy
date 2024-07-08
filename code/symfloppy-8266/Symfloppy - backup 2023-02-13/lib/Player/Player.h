#ifndef Player_h
#define Player_h

#include <Arduino.h>
#include <MidiFileStream.h>
#include <LittleFS.h>
#include <DataStack.h>
#include <Note.h>

class Player {
    public:
        
        File file;
        MidiFileStream midi_file;
        unsigned int channel;
        String file_name;
        int micros_per_tick;

        DataStack<Note> * note_data_stack;


        Player();

        void setChannel(unsigned int channel);
        void setFileName(String file_name);
        void load();
        int midiNoteToFrequency(int midi_note);

        void play();

};

#endif