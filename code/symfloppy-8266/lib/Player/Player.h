#ifndef Player_h
#define Player_h

#include <Arduino.h>
#include <MidiFileStream.h>
#include <LittleFS.h>
#include <Note.h>


typedef std::function<void(Note * note)> NoteEventFunction;
typedef std::function<void()> StopPlayingEventFunction;

class Player {
    public:
        Player();

        boolean load();
        void setChannel(unsigned int channel);
        void setFileName(String file_name);
        void onNoteEvent(NoteEventFunction on_note_function);
        void onStopPlayingEvent(StopPlayingEventFunction on_stop_playing_function);
        void findNextNote();

        void play();
        void pause();
        void stop();
        void update();

    private:
        String file_name;
        File file;
        MidiFileStream midi_file;
        int midi_format;
        int micros_per_tick;

        unsigned int channel;

        boolean is_finished;
        boolean error_occurred;
        boolean is_playing;

        unsigned long time_millis;
        Note * note;
        NoteEventFunction on_note_function;
        StopPlayingEventFunction on_stop_playing_function;

        void closeFile();
};

#endif