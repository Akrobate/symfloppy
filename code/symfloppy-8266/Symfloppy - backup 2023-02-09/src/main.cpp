#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <MidiFileStream.h>


// *************************************************************************************************
//
// https://www.raspberryme.com/point-dacces-ap-esp8266-nodemcu-pour-serveur-web/
// https://randomnerdtutorials.com/esp8266-nodemcu-async-web-server-espasyncwebserver-library/
//
// FileUpdoad
// https://github.com/smford/esp32-asyncwebserver-fileupload-example/blob/master/example-01/example-01.ino
//
// Handle Post Data
// https://techtutorialsx.com/2018/10/12/esp32-http-web-server-handling-body-data/
//
// Floppy
// http://dduino.blogspot.com/2011/10/moppy-playing-music-with-floppy-drives.html
//
// LittleFS test
// https://www.raspberryme.com/esp8266-vs-code-platformio-telecharger-des-fichiers-sur-le-systeme-de-fichiers-littlefs/
//
// Tonefunction
// https://www.carnetdumaker.net/articles/jouer-des-notes-de-musiques-avec-une-carte-arduino-genuino/#:~:text=La%20fonction%20tone()%20permet%20de%20g%C3%A9n%C3%A9rer%20un%20signal%20de,subtile%2C%20mais%20elle%20change%20tout.
//
// *************************************************************************************************

#define SERVER_PORT           80
#define DEFAULT_MIDI_CHANNEL  14


const char index_html[] PROGMEM = R"rawliteral(
<meta name=viewport content="width=device-width,initial-scale=1"><style>.block-position{max-width:500px;margin-left:auto;margin-right:auto}body{font-family:Arial,Helvetica}.block{border:1px solid grey;border-radius:10px;padding:20px;margin-bottom:20px}.block .title{font-weight:700}.block .content{margin:20px}span{font-style:italic}.valid{color:#060}.error{color:red}button{width:140px;height:30px;border:1px solid grey;border-radius:10px}.center{text-align:center}</style><h1 class=block-position><span style=color:red>S</span><span style=color:grey>ym</span>floppy</h1><div class="block block-position"><div class=title>Bienvenue</div><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</div><div class="block block-position"><div class=title>Midi input channel</div><div class=content><select name=channel id=select_channel_save></select></div><div class=content><span id=span_channel_help></span></div><div class="content center"><button type=button id=button_channel_save>Save</button></div></div><div class="block block-position"><div class=title>Fichier Music box</div><div class=content><input type=file id=input_file></div><div class=content><span id=span_upload_help></span></div><div class="content center"><button type=button id=button_upload>Upload</button></div></div><p class=block-position style=text-align:right id=corporate_mention>Software version: v1.0</p><script>const button_channel_save=document.getElementById("button_channel_save"),select_channel_save=document.getElementById("select_channel_save"),input_file=document.getElementById("input_file"),button_upload=document.getElementById("button_upload"),span_upload_help=document.getElementById("span_upload_help"),span_channel_help=document.getElementById("span_channel_help"),corporate_mention=document.getElementById("corporate_mention");function message(e,n,a=""){e.classList.remove("valid"),e.classList.remove("error"),a&&e.classList.add(a),e.innerText=n}for(let e=1;e<17;e++){const n=document.createElement("option");n.innerText="channel "+e,n.value=e,select_channel_save.appendChild(n)}fetch("/channel").then((e=>e.json())).then((e=>select_channel_save.value=e)),button_channel_save.addEventListener("click",(async()=>{const e=select_channel_save.value;try{let n=new FormData;n.append("channel",e),await fetch("/channel",{body:n,method:"POST"}),message(span_channel_help,"Channel saved","valid")}catch(e){message(span_channel_help,"Error occured","error")}})),button_upload.addEventListener("click",(async()=>{const e=input_file.files[0];if(void 0===e)return void message(span_upload_help,"Please select file first","error");if(e.size>1e5)return void message(span_upload_help,`File size is too large (${Math.ceil(e.size/1e3)}kb), max file size is 100kb`,"error");message(span_upload_help,"Uploading...");const n=new FormData;n.append("file",input_file.files[0]),console.log(n);try{await fetch("/upload",{method:"POST",body:n})}catch(e){message(span_upload_help,"Error occured","error")}message(span_upload_help,"File uploaded","valid")}))</script>
)rawliteral";



const String ssid = "ESP8266_SSID_1";

int channel = DEFAULT_MIDI_CHANNEL;

AsyncWebServer server(SERVER_PORT);


MidiFileStream midiFile;
File file;
boolean errorOccurred;  // if true, there's a problem.
boolean isFinished;     // if true, we successfully finished reading the file.



const byte PIN_BUZZER = 5;
const byte pinLed = 15;
void setup() {

  Serial.begin(115200);


  const String mac_address = WiFi.macAddress();
  String mac_serial = WiFi.macAddress();
  String mac_serial_truncated;
  mac_serial.replace(":","");
  mac_serial_truncated = mac_serial.substring(0, 4);

  // Wifi connection as AP
  // WiFi.softAP(ssid);


  // Debug wifi connection as STA
  WiFi.begin("LiveboxLA", "Kzen=813;");
  int wifi_max_try = 5;
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
  // Endd Debug wifi connection as STA



  server.onNotFound(
    [](AsyncWebServerRequest *request){
      request->send(404, "text/html", "Not found");
    }
  );


  server.on(
    "/",
    HTTP_GET,
    [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html);
    }
  );


  server.on(
    "/channel",
    HTTP_GET,
    [](AsyncWebServerRequest *request){
      Serial.println("GET /channel - channel : " + String(channel));
      request->send(200, "text/html", String(channel));
    }
  );


  server.on(
    "/channel",
    HTTP_POST,
    [](AsyncWebServerRequest *request){
      for (int i = 0; i < request->params(); i++) {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        if (p->name() == "channel") {
          channel = p->value().toInt();
        }
      }
      request->send_P(200, "text/html", "OK");
    }
  );


  server.on(
    "/upload",
    HTTP_POST,
    [](AsyncWebServerRequest *request) {
      Serial.println("In upload route");
      request->send(200, "text/html", "FILE UPLOADED");
    },
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
      
      Serial.println("in handleUpload");
      String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();
      Serial.println(logmessage);

      if (!index) {
        logmessage = "Upload Start: " + String(filename);
        // request->_tempFile = SPIFFS.open("/" + filename, "w");
        Serial.println(logmessage);
      }

      if (len) {
        // request->_tempFile.write(data, len);
        logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
        Serial.println(logmessage);
      }

      if (final) {
        logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
        // request->_tempFile.close();
        Serial.println(logmessage);
      }
    }
  );

  server.begin();



  Serial.println("In setup testing");
  delay(5000);
  Serial.println("Starting testing");







  // ####################################################################################################
  // LittleFS Working example
  // ####################################################################################################
  /*
  
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
  File file = LittleFS.open("/test.txt", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  */

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
  file = LittleFS.open("/Undertale_-_Megalovania.mid", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File opened");
  
  
  if (!midiFile.begin(file)) {
    Serial.print("Failed to open Midi file: ");
    Serial.print("Check: is it a Midi-format file?");
    
    // Clean up
    midiFile.end();
    file.close();
    
    return;
  }


  // Say what the Midi Header told us.
  Serial.print("Midi file format: ");
  Serial.println(midiFile.getFormat());
  Serial.print("Number of tracks: ");
  Serial.println(midiFile.getNumTracks());
  Serial.print("Ticks per beat: ");
  Serial.println(midiFile.getTicksPerBeat());

    // Open the first track of the file.
  if (midiFile.openChunk() != CT_MTRK) {
    Serial.println("Failed to open the first track of the file.");
    
    // Clean up
    midiFile.end();
    file.close();
    
    return;
  }




  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(pinLed, OUTPUT);

}



unsigned long fps = 0;
unsigned long currentTime=0;
unsigned long previousTime=0;
int secs = 30;


int code_int = 0;


void loop() {
  // put your main code here, to run repeatedly:

  fps++;

  // delay(5000);
  // Serial.println("Started...");

  if((millis() - previousTime) > (secs * 1000)){
    previousTime = millis();
    Serial.println("FPS rate : " + String(fps / secs));
    fps = 0;
  }
  
 
// If we're finished reading, do nothing.
  if (isFinished) {
    return;
  }
  
  // If there is a problem, just blink the LED.
  if (errorOccurred) {
    if ((millis() % 1000) < 500) {
      digitalWrite(pinLed, HIGH);
    } else {
      digitalWrite(pinLed, LOW);
    }
    
    return;
  }
  
  // read the next Midi event from the file.
  event_t eventType = midiFile.readEvent();
  if (eventType == ET_END) {
    Serial.println("ET_END ****************************************************************");
    // The track has ended; open the next track.
    chunk_t chunkType = midiFile.openChunk();
    if (chunkType != CT_MTRK) {
      if (chunkType == CT_END) {
        Serial.println("File ended normally.");
        
        // Clean up
        midiFile.end();
        file.close();
        
        isFinished = true;
        return;
      }
      
      // File error: Chunk is not a track.
      Serial.println("Failed to open file track.");
    
      // Clean up
      midiFile.end();
      file.close();
    
      errorOccurred = true;
      return;
    }
    Serial.println("CT_MTRK ****************************************************************");
    // Successfully opened the track
    // loop again to read the next event.
    
    return;
  }
  
  // Say something about this event
  Serial.print("delay ");
  Serial.print(midiFile.getEventDeltaTicks());
  Serial.println(" ticks.");
  
  if (eventType == ET_TEMPO) {
    Serial.print("New Tempo: ");
    Serial.print(midiFile.getEventDataP()->tempo.uSecPerBeat);
    Serial.println(" microseconds per beat.");

    // timer
    // microsPerTick = midiFile.getEventDataP()->tempo.uSecPerBeat / midiFile.getTicksPerBeat();

    return;
  }

  // timer
  // uSecs = midiFile.getEventDeltaTicks() * microsPerTick;

  if (eventType == ET_END_TRACK) {
    Serial.println("End of Track event.");
    return;
  }
  
  if (eventType == ET_CHANNEL) {
    char code = midiFile.getEventDataP()->channel.code;
    

    if (code == CH_NOTE_OFF) {
      Serial.print("Note Off: Midi note number ");
      Serial.print(midiFile.getEventDataP()->channel.param1);
      Serial.print(" ");
      Serial.println(midiFile.getEventDataP()->channel.chan);
      return;
    }

    if (code == CH_NOTE_ON) {
      Serial.print("Note On: Midi note number ");
      Serial.print(midiFile.getEventDataP()->channel.param1);
      Serial.print(" ");
      Serial.println(midiFile.getEventDataP()->channel.chan);
      return;
    }
    
    // Otherwise, it's a Channel event that we don't care about
    // Ignore it.    
    return;
  }




  
}




/*

tone(PIN_BUZZER, 2637, 200);delay(400);
tone(PIN_BUZZER, 1975, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 2349, 200);delay(400);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 1975, 200);delay(200);
tone(PIN_BUZZER, 1760, 200);delay(400);
tone(PIN_BUZZER, 1760, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 2637, 200);delay(400);
tone(PIN_BUZZER, 2349, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 1975, 200);delay(400);
tone(PIN_BUZZER, 1975, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 2349, 200);delay(400);
tone(PIN_BUZZER, 2637, 200);delay(400);
tone(PIN_BUZZER, 2093, 200);delay(400);
tone(PIN_BUZZER, 1760, 200);delay(400);
tone(PIN_BUZZER, 1760, 200);delay(800);
tone(PIN_BUZZER, 1760, 200);delay(400);
tone(PIN_BUZZER, 2349, 200);delay(200);
tone(PIN_BUZZER, 2794, 200);delay(200);
tone(PIN_BUZZER, 3520, 200);delay(400);
tone(PIN_BUZZER, 3136, 200);delay(200);
tone(PIN_BUZZER, 2794, 200);delay(200);
tone(PIN_BUZZER, 2637, 200);delay(600);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 2637, 200);delay(400);
tone(PIN_BUZZER, 2349, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 1975, 200);delay(400);
tone(PIN_BUZZER, 1975, 200);delay(200);
tone(PIN_BUZZER, 2093, 200);delay(200);
tone(PIN_BUZZER, 2349, 200);delay(400);
tone(PIN_BUZZER, 2637, 200);delay(400);
tone(PIN_BUZZER, 2093, 200);delay(400);
tone(PIN_BUZZER, 1760, 200);delay(400);
tone(PIN_BUZZER, 1760, 200);delay(800);

*/