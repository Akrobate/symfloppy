#pragma once

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <configurations.h>

class MidiFileManager {

    private:
        String directory;

    public:
        static const int MAX_FILES = 100;
        int fileCount = 0;
        struct MidiFile {
            String name;
            size_t size;
        };
        MidiFile midiFiles[MAX_FILES];


        MidiFileManager();
        void init();

        // void loadFiles(const String& directory);
        void loadFiles(String directory);
        void reload();
        int getFileCount();
        const MidiFile* getFileAt(int index) const;

};
