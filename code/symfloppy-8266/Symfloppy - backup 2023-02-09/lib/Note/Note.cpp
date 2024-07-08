#include "Note.h"

Note::Note() {
}

Note::Note(int note, unsigned int event_delta_ticks) {
    this->note = note;
    this->event_delta_ticks = event_delta_ticks;
}


void Note::setNote(int note) {
    this->note = note;
}

int Note::getNote() {
    return this->note;
}

void Note::setEventDeltaTicks(unsigned int event_delta_ticks) {
    this->event_delta_ticks = event_delta_ticks;
}

unsigned int Note::getEventDeltaTicks() {
    return this->event_delta_ticks;
}