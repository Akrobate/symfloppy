#include "Player.h"

Player::Player() {
    this->micros_per_tick = 0;
    this->note = new Note(-1, 0);

    this->time_millis = millis();

    this->is_finished = false;
    this->error_occurred = false;
    this->is_playing = false;

}


void Player::setChannel(unsigned int channel) {
    this->channel = channel;
}


void Player::setFileName(String file_name) {
    this->file_name = file_name;
}


boolean Player::load() {

    if(!LittleFS.begin()){
        return false;
    }
  
    this->file = LittleFS.open(this->file_name, "r");
    if(!this->file){
        return false;
    }
  
    if (!this->midi_file.begin(file)) {
        this->closeFile();
        return false;
    }

    this->midi_format = this->midi_file.getFormat();

    if (this->midi_file.openChunk() != CT_MTRK) {
        this->closeFile();
        return false;
    }

    return true;
}


void Player::findNextNote() {

    boolean usefull_data_found = false;

    while(!this->is_finished && !this->error_occurred && !usefull_data_found) {
  
        event_t eventType = this->midi_file.readEvent();

        if (eventType == ET_END) {
            chunk_t chunkType = this->midi_file.openChunk();
            if (chunkType != CT_MTRK) {
                if (chunkType == CT_END) {
                    this->closeFile();
                    this->is_finished = true;
                    this->is_playing = false;
                    continue;
                }
                this->closeFile();    
                this->error_occurred = true;
                continue;
            }
            continue;
        }

        if (eventType == ET_TEMPO) {
            this->micros_per_tick = this->midi_file.getEventDataP()->tempo.uSecPerBeat / this->midi_file.getTicksPerBeat();
            continue;
        }

        if (eventType == ET_END_TRACK) {
            continue;
        }

        if (eventType == ET_CHANNEL) {

            char code = this->midi_file.getEventDataP()->channel.code;
            if (midi_file.getEventDataP()->channel.chan != (this->channel - 1) || (code != CH_NOTE_OFF && code != CH_NOTE_ON)) {
                continue;
            }

            this->note->setEventDeltaMillis((this->midi_file.getEventDeltaTicks() * this->micros_per_tick) / 1000);

            if (code == CH_NOTE_OFF) {
                this->note->setNoteOff();
            }

            if (code == CH_NOTE_ON) {
                if (this->midi_file.getEventDataP()->channel.param2 == 0) {
                    this->note->setNoteOff();
                } else {
                    this->note->setNote(this->midi_file.getEventDataP()->channel.param1);
                }
            }
            usefull_data_found = true;
            continue;
        }
    }
}


void Player::closeFile() {
    this->midi_file.end();
    this->file.close();
}



void Player::update() {
    if (this->is_playing && !this->is_finished && !this->error_occurred) {
        if (millis() - time_millis > this->note->getEventDeltaMillis()) {
            time_millis = millis();
            this->on_note_function(this->note);
            this->findNextNote();
        }
    }
}


void Player::onNoteEvent(NoteEventFunction on_note_function) {
    this->on_note_function = on_note_function;
}


void Player::play() {
    this->is_playing = true;
}


void Player::pause() {
    this->is_playing = false;
}
