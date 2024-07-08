#include <Arduino.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte pinLed = 4;


void setup() {

    // Serial.begin(31250);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    delay(500);

    Serial.swap();
    delay(500);
    
    MIDI.turnThruOn();

/*
    MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
        Serial.write(1);
        Serial.write(channel);
        Serial.write(note);
        Serial.write(velocity);
    });

    MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
        Serial.write(0);
        Serial.write(channel);
        Serial.write(note);
        Serial.write(velocity);
    });

*/
    pinMode(pinLed, OUTPUT);

    digitalWrite(pinLed, HIGH);
    delay(500);
    digitalWrite(pinLed, LOW);
    delay(500);

    digitalWrite(pinLed, HIGH);
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(100);
    digitalWrite(pinLed, HIGH);
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(100);

}

void loop() {
    MIDI.read();
}



// https://www.falstad.com/circuit/circuitjs.html?ctz=CQAgjCAMB0l3BWcMBMcUHYMGZIA4UA2ATmIxAUgoqoQFMBaMMAKABZJy3C3xiUQ3XtmyFwLAE6CefAdjy8w-KCBRoWAcwqEqIsQh2C4KyCwDu04aMuqUvUwCUQuRWAF2qzAVSodqPqGgEFgBnZ0hFZXlI73AQADMAQwAbELpzcNcBA083KAyhZ2scorFTCxK1XhK9fKkSr21PZSo1cqbZEB5m7xYnF06PToC-bGhsE0Dgi2ZrJQFZsVr2vBlaxdL8i1WY5AwFlskQHfA8k-mVNoyTquO163aMQjxNk+WWMEIFzgOFsDnlAIACZ0JIAV2SABcGMk6EC4gEYJBWE5znliGwspM-EhEUEjk8XhdusNbKYOORCZ0qesMjVrDSHhkqbdGWUWEA
