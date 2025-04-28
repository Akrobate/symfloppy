#include "Note.h"

const int MIDI_FREQUENCY_MAPPING[] = {8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

Note::Note() {
}

Note::Note(int note, unsigned int event_delta_millis) {
    this->note = note;
    this->event_delta_millis = event_delta_millis;
}

void Note::setNoteOff() {
    this->setNote(-1);
}

boolean Note::isNoteOn() {
    return (this->getNote() > 0);
}

void Note::setNote(int note) {
    this->note = note;
}

int Note::getNote() {
    return this->note;
}

void Note::setEventDeltaMillis(unsigned int event_delta_millis) {
    this->event_delta_millis = event_delta_millis;
}

unsigned int Note::getEventDeltaMillis() {
    return this->event_delta_millis;
}

int Note::midiNoteToFrequency(int midi_note) {
    return MIDI_FREQUENCY_MAPPING[midi_note];
}

int Note::getFrequency() {
    return this->midiNoteToFrequency(this->note);
}