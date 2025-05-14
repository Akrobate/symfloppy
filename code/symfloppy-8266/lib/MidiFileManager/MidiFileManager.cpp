#include "MidiFileManager.h"

MidiFileManager::MidiFileManager() {
    // Constructor
}

void MidiFileManager::init() {
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }
    Serial.println("File system mounted successfully");
}

void MidiFileManager::loadFiles(String directory) {
    this->directory = directory;
    fileCount = 0;
    Dir dir = LittleFS.openDir(directory);
  
    while (dir.next() && fileCount < MAX_FILES) {
      String name = dir.fileName();
      if (name.endsWith(".mid") || name.endsWith(".midi")) {
        midiFiles[fileCount].name = name;
        midiFiles[fileCount].size = dir.fileSize();
        fileCount++;
      }
    }
}


void MidiFileManager::reload() {
    this->loadFiles(this->directory);
}


int MidiFileManager::getFileCount() {
    return fileCount;
}


const MidiFileManager::MidiFile* MidiFileManager::getFileAt(int index) const {
    if (index < 0 || index >= fileCount) return nullptr;
    return &midiFiles[index];
  }