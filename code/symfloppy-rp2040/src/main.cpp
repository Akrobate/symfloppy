#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>
#include "configuration.h"


// Initialise USB MIDI
Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

const uint8_t NOTE_NUMBER = 60; // Do central (C4)
const uint8_t VELOCITY = 127;
bool note_state = false;

void setup() {
    // Computer name / description
    USBDevice.setManufacturerDescriptor("Artiom Labs");
    USBDevice.setProductDescriptor("Pico MIDI Controller");

    // Initialise MIDI protocole
    MIDI.begin(MIDI_CHANNEL_OMNI);

    // wait for USB etablished (optionnal)
    while (!TinyUSBDevice.mounted()) {
        delay(1);
    }
}

void loop() {
    if (!note_state) {
        MIDI.sendNoteOn(NOTE_NUMBER, VELOCITY, 1);
        note_state = true;
    } else {
        MIDI.sendNoteOff(NOTE_NUMBER, 0, 1);
        note_state = false;
    }
    delay(1000); 
}