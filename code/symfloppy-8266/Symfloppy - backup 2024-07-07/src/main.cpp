#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <Player.h>
#include <FrequencyGenerator.h>
#include <MIDI.h>

#include <SymfloppyServer.h>





MIDI_CREATE_DEFAULT_INSTANCE();

#define SERVER_PORT           80
#define DEFAULT_MIDI_CHANNEL  14

const String ssid = "ESP8266_SSID_1";

int channel = DEFAULT_MIDI_CHANNEL;

const byte PIN_BUZZER = 5;
const byte pinLed = 4;

FrequencyGenerator * frequency_generator = new FrequencyGenerator(PIN_BUZZER);
Player * player = new Player();
SymfloppyServer * server = new SymfloppyServer(SERVER_PORT);

void setup() {

  pinMode(pinLed, OUTPUT);

  digitalWrite(pinLed, LOW);
  
  // Serial.begin(31250);
  // Serial.swap();
  // MIDI.begin(MIDI_CHANNEL_OMNI);


  Serial.begin(115200);
  
  // MIDI.turnThruOff();

  MIDI.setHandleNoteOn([](byte channel, byte pitch, byte velocity) {
    if (velocity > 0) {
      digitalWrite(pinLed, HIGH);
    } else {
      digitalWrite(pinLed, LOW);  
    }
  });

  MIDI.setHandleNoteOff([](byte channel, byte pitch, byte velocity) {
    digitalWrite(pinLed, LOW);
  });

  // Serial.begin(115200);

  const String mac_address = WiFi.macAddress();
  String mac_serial = WiFi.macAddress();
  String mac_serial_truncated;
  mac_serial.replace(":","");
  mac_serial_truncated = mac_serial.substring(0, 4);

  delay(1000);
  // Wifi connection as AP
  WiFi.softAP(ssid);


  // Debug wifi connection as STA
  WiFi.begin("LiveboxLA", "Kzen=813;");
  int wifi_max_try = 5;
  // Serial.print("Connecting");
  int count_try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    // Serial.print(".");
    count_try++;
  }
  // Serial.println();
  // Serial.print("Connected, IP address: ");
  // Serial.println(WiFi.localIP());
  // Endd Debug wifi connection as STA


  server->init();
  server->begin();

  // Serial.println("Loading file");

  player->setFileName("/Undertale_-_Megalovania.mid");
  //player->setFileName("/test_gamme.mid");


  player->setChannel(2);
  player->load();

  player->onNoteEvent([](Note * note) {
    if (note->isNoteOn()) {
      frequency_generator->setFrequency(note->getFrequency());
      frequency_generator->start();
        void update();
    } else {
      frequency_generator->stop();
    }
  });

  // Uncomment to make it play the file
  player->play();

}


void loop() {
  player->update();
  frequency_generator->update();
  // MIDI.read();
}
