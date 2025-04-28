#include "Player.h"

const int MIDI_FREQUENCY_MAPPING[] = {8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

Player::Player() {
    this->micros_per_tick = 0;
    this->note_data_stack = new DataStack<Note>();
}


void Player::setChannel(unsigned int channel) {
    this->channel = channel;
}


void Player::setFileName(String file_name) {
    this->file_name = file_name;
}


void Player::load() {


    // GENERIC Opening file

    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
  
    this->file = LittleFS.open(this->file_name, "r");
    if(!this->file){
        Serial.println("Failed to open file for reading");
        return;
    }
  
    Serial.println("File opened");
  
    if (!this->midi_file.begin(file)) {
        Serial.print("Failed to open Midi file: ");
        Serial.print("Check: is it a Midi-format file?");
        
        this->midi_file.end();
        this->file.close();
    }

    // Say what the Midi Header told us.
    Serial.print("Midi file format: ");
    Serial.println(this->midi_file.getFormat());
    Serial.print("Number of tracks: ");
    Serial.println(this->midi_file.getNumTracks());
    Serial.print("Ticks per beat: ");
    Serial.println(this->midi_file.getTicksPerBeat());

    // Open the first track of the file.
    if (this->midi_file.openChunk() != CT_MTRK) {
        Serial.println("Failed to open the first track of the file.");
        this->midi_file.end();
        this->file.close();
        return;
    }


    // Looping on content
    // Looping on content
    // Looping on content

    boolean isFinished = false;
    boolean errorOccurred = false;
    long messages_count = 0;
    while(!isFinished && !errorOccurred) {
  
        event_t eventType = this->midi_file.readEvent();

        if (eventType == ET_END) {
            Serial.println("ET_END ****************************************************************");
            // The track has ended; open the next track.
            chunk_t chunkType = this->midi_file.openChunk();
            if (chunkType != CT_MTRK) {
                if (chunkType == CT_END) {
                    Serial.println("File ended normally.");
                    this->midi_file.end();
                    this->file.close();
                    isFinished = true;
                    continue;
                }
                
                Serial.println("Failed to open file track.");
                
                // Clean up
                this->midi_file.end();
                this->file.close();
                
                errorOccurred = true;
                continue;
            }
            Serial.println("CT_MTRK ****************************************************************");
            // Successfully opened the track
            // loop again to read the next event.
            continue;
        }


        if (eventType == ET_TEMPO) {
            Serial.print("New Tempo: ");
            Serial.print(this->midi_file.getEventDataP()->tempo.uSecPerBeat);
            Serial.println(" microseconds per beat.");
            // timer
            this->micros_per_tick = this->midi_file.getEventDataP()->tempo.uSecPerBeat / this->midi_file.getTicksPerBeat();
            continue;
        }


        if (eventType == ET_END_TRACK) {
            Serial.println("End of Track event.");
            continue;
        }


        if (eventType == ET_CHANNEL) {

            if (midi_file.getEventDataP()->channel.chan != (this->channel - 1)) {
                continue;
            }
            // Say something about this event
            Serial.print("delay ");
            Serial.print(this->midi_file.getEventDeltaTicks());
            Serial.println(" ticks.");

            unsigned int delta_millis = (this->midi_file.getEventDeltaTicks() * this->micros_per_tick) / 1000;

            Serial.print("delta_millis ");
            Serial.print(delta_millis);
            Serial.println(" millis.");


            char code = this->midi_file.getEventDataP()->channel.code;

            if (code == CH_NOTE_OFF) {
                Serial.print("Note Off: Midi note number ");
                Serial.print(this->midi_file.getEventDataP()->channel.param1);
                Serial.print(" f: ");
                Serial.print(this->midiNoteToFrequency(this->midi_file.getEventDataP()->channel.param1));
                Serial.print(" v: ");
                Serial.print(this->midi_file.getEventDataP()->channel.param2);
                Serial.print(" ch: ");
                Serial.println(this->midi_file.getEventDataP()->channel.chan);

Serial.println("Freee memory");
Serial.println(ESP.getFreeHeap());

                this->note_data_stack->push(
                    new Note(
                        -1,
                        delta_millis)
                );
messages_count++;
                continue;
            }

            if (code == CH_NOTE_ON) {
                Serial.print("Note On: Midi note number ");
                Serial.print(this->midi_file.getEventDataP()->channel.param1);
                Serial.print(" f: ");
                Serial.print(this->midiNoteToFrequency(this->midi_file.getEventDataP()->channel.param1));
                Serial.print(" v: ");
                Serial.print(this->midi_file.getEventDataP()->channel.param2);
                Serial.print(" ch: ");
                Serial.println(this->midi_file.getEventDataP()->channel.chan);

Serial.println("Freee memory");
Serial.println(ESP.getFreeHeap());

                this->note_data_stack->push(
                    new Note(
                        this->midiNoteToFrequency(this->midi_file.getEventDataP()->channel.param1),
                        delta_millis)
                );
messages_count++;
                continue;
            }

            continue;
        }

    }


    Serial.println("total =========================");
    Serial.println(messages_count);

}


int Player::midiNoteToFrequency(int midi_note) {
    return MIDI_FREQUENCY_MAPPING[midi_note];
}


void Player::play() {
    const byte PIN_BUZZER = 5;
    pinMode(PIN_BUZZER, OUTPUT);
    Note * note;
    while(note = this->note_data_stack->getNext()) {
        delay(note->getEventDeltaTicks());
        if (note->getNote() > 0) {
            tone(PIN_BUZZER, note->getNote());
        } else {
            noTone(PIN_BUZZER);
        }
    }
}
