#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <Player.h>
#include <FrequencyGenerator.h>
#include <secrets.h>

#include <FastLED.h>
#include <SymfloppyServer.h>

#define SERVER_PORT           80
#define DEFAULT_MIDI_CHANNEL  14

const String ssid = "ESP8266_SSID_1";

int channel = DEFAULT_MIDI_CHANNEL;

const byte PIN_BUZZER = 5;    // GPIO 5   // D1
const byte PIN_NEOPIXEL_LED = 15;  // GPIO 15  // D8
const byte PIN_BUTTON_LEFT = 4;    // GPIO 4   // D2
const byte PIN_BUTTON_RIGHT = 13;   // GPIO 13  // D7
const byte PIN_BUTTON_MIDDLE = 12;  // GPIO 12  // D6


FrequencyGenerator * frequency_generator = new FrequencyGenerator(PIN_BUZZER);
Player * player = new Player();
SymfloppyServer * server = new SymfloppyServer(SERVER_PORT);

CRGB leds[3];


void setup() {
  
  Serial.begin(115200);
  
  pinMode(PIN_NEOPIXEL_LED, OUTPUT);
  digitalWrite(PIN_NEOPIXEL_LED, LOW);
  for(int i = 0; i < 3; i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(leds, 3);
  FastLED.clear();
  FastLED.delay(1);
  FastLED.show();

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
      leds[0] = CRGB::Green;
      FastLED.delay(1);
      FastLED.show();
      frequency_generator->setFrequency(note->getFrequency());
      frequency_generator->start();
    } else {
      leds[0] = CRGB::Black;
      FastLED.delay(1);
      FastLED.show();
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
}
