#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>

#include <FrequencyGenerator.h>
#include <SymfloppyServer.h>
#include <Player.h>
#include <ButtonsInterface.h>
#include <LedInterface.h>

#include <configurations.h>
#include <secrets.h>


const String ssid = "ESP8266_SSID_1";

int channel = DEFAULT_MIDI_CHANNEL;

FrequencyGenerator * frequency_generator = new FrequencyGenerator(PIN_BUZZER);
Player * player = new Player();
SymfloppyServer * server = new SymfloppyServer(SERVER_PORT);
ButtonsInterface * buttons_interface = new ButtonsInterface();
LedInterface * led_interface = new LedInterface();

void setup() {
  
  Serial.begin(115200);

  led_interface->init();
  
  const String mac_address = WiFi.macAddress();
  String mac_serial = WiFi.macAddress();
  String mac_serial_truncated;
  mac_serial.replace(":","");
  mac_serial_truncated = mac_serial.substring(0, 4);

  delay(1000);
  WiFi.softAP(ssid);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  int count_try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    count_try++;
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

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
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    Serial.print("Connecting");
  
    int count_try = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
      Serial.print(".");
      count_try++;
    }
  
    Serial.println("Playing finished, restarting wifi connection");
  });

  // Uncomment to make it play the file
  player->play();
  WiFi.disconnect(true, false); 
  WiFi.mode(WIFI_OFF);

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
