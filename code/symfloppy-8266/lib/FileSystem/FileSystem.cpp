#include "FileSystem.h"

FileSystem::FileSystem() {
    this->fs = &LittleFS;
}


void FileSystem::init() {
    if (!this->fs->begin()) {
        Serial.println("Failed to mount file system");
    } else {
        Serial.println("File system mounted successfully");
    }
}


fs::FS * FileSystem::getFS() {
    if (!this->is_inited) {
        this->init();
        this->is_inited = true;
    }
    return this->fs;
}
