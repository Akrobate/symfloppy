#include <Arduino.h>
#include <ESPAsyncTCP.h>

#include <WifiManager.h>
#include <FrequencyGenerator.h>
#include <SymfloppyServer.h>
#include <Player.h>
#include <ButtonsInterface.h>
#include <LedInterface.h>

#include <configurations.h>
#include <secrets.h>

int channel = DEFAULT_MIDI_CHANNEL;

FrequencyGenerator * frequency_generator = new FrequencyGenerator(PIN_BUZZER);
Player * player = new Player();
SymfloppyServer * server = new SymfloppyServer(SERVER_PORT);
ButtonsInterface * buttons_interface = new ButtonsInterface();
LedInterface * led_interface = new LedInterface();
WifiManager * wifi_manager = new WifiManager();

void setup() {

    Serial.begin(115200);
    led_interface->init();
    wifi_manager->startAccessPoint();
    wifi_manager->connect();
    server->init();
    server->begin();

    // Serial.println("Loading file");
    // player->setFileName("/Undertale_-_Megalovania.mid");
    // player->setFileName("/I_Was_Made_for_Loving_You.mid");
    player->setFileName("/gamme_2.mid");

    player->setChannel(1);
    player->load();

    player->onNoteEvent([](Note * note) {
        if (note->isNoteOn()) {
            frequency_generator->setFrequency(note->getFrequency());
            frequency_generator->start();
        } else {
            frequency_generator->stop();
        }
    });

    player->onStopPlayingEvent([]() {
        frequency_generator->stop();
        wifi_manager->reconnect();
        Serial.println("Playing finished, restarting wifi connection");
    });

    player->play();
    wifi_manager->disconnect();
}


void loop() {
    player->update();
    frequency_generator->update();
    buttons_interface->update();

    if (buttons_interface->onLeft()) {
        led_interface->onRed();
    }

    if (buttons_interface->onRight()) {
        led_interface->off();
    }
}
