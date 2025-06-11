#include <Arduino.h>
#include <ESPAsyncTCP.h>

#include <WifiManager.h>
#include <MidiFileManager.h>
#include <FrequencyGenerator.h>
#include <SymfloppyServer.h>
#include <Player.h>
#include <ButtonsInterface.h>
#include <LedInterface.h>
#include <FileSystem.h>

#include <configurations.h>
#include <secrets.h>

int channel = DEFAULT_MIDI_CHANNEL;

FrequencyGenerator * frequency_generator = new FrequencyGenerator(PIN_BUZZER);
Player * player = new Player();
SymfloppyServer * server = new SymfloppyServer(SERVER_PORT);
ButtonsInterface * buttons_interface = new ButtonsInterface();
LedInterface * led_interface = new LedInterface();
WifiManager * wifi_manager = new WifiManager();
MidiFileManager * midi_file_manager = new MidiFileManager();
FileSystem * file_system = new FileSystem();

void setup() {

    Serial.begin(115200);
    led_interface->init();

    file_system->init();

    wifi_manager->startAccessPoint();
    wifi_manager->connect();

    midi_file_manager->init();
    midi_file_manager->loadFiles("/");
    for (int i = 0; i < midi_file_manager->getFileCount(); i++) {
      const MidiFileManager::MidiFile* file = midi_file_manager->getFileAt(i);
      if (file) {
        Serial.printf("Fichier %d: %s (%d octets)\n", i, file->name.c_str(), file->size);
      }
    }

    server->injectMidiFileManager(midi_file_manager);
    server->init();
    server->begin();

    player->setChannel(1);

    player->onNoteEvent([](Note * note) {
        if (note->isNoteOn()) {
            frequency_generator->setFrequency(note->getFrequency());
            frequency_generator->start();
            led_interface->onGreen();
        } else {
            frequency_generator->stop();
            led_interface->off();
        }
    });

    player->onStopPlayingEvent([]() {
        frequency_generator->stop();
        // wifi_manager->reconnect();
        // Serial.println("Playing finished, restarting wifi connection");
    });

    // player->play();
    // wifi_manager->disconnect();
}

bool is_playing = false;
bool is_paused = false;

int playing_file_index = 0;


void playFile(int file_index) {
    const MidiFileManager::MidiFile* file = midi_file_manager->getFileAt(file_index);
    if (file) {
        player->stop();
        player->setFileName(file->name);
        player->load();
        player->play();
        is_playing = true;
        Serial.println("Playing file: " + file->name);
    } else {
        Serial.println("Invalid file index");
    }
}

void stop() {
    player->stop();
    is_playing = false;
}

void playNextFile() {
    playing_file_index++;
    if (playing_file_index >= midi_file_manager->getFileCount()) {
        playing_file_index = 0;
    }
    playFile(playing_file_index);
}

void playPreviousFile() {
    playing_file_index--;
    if (playing_file_index < 0) {
        playing_file_index = midi_file_manager->getFileCount() - 1;
    }
    playFile(playing_file_index);
}



void loop() {
    player->update();
    frequency_generator->update();
    buttons_interface->update();

    if (buttons_interface->onLeft()) {
        playPreviousFile();
        // led_interface->onRed();
    }

    if (buttons_interface->onRight()) {
        playNextFile();
        // led_interface->off();
    }


    if (buttons_interface->onMiddle()) {
        if (is_playing) {
            stop();
            led_interface->off();
        } else {
            playFile(playing_file_index);
            led_interface->onGreen();
        }
    }

}
