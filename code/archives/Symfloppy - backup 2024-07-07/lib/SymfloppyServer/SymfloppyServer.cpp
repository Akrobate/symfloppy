#include "SymfloppyServer.h"

SymfloppyServer::SymfloppyServer(int port) {
    this->server = new AsyncWebServer(port);
    this->channel = 12;
}


void SymfloppyServer::begin() {
    this->server->begin();
}


void SymfloppyServer::init() {

  this->server->onNotFound(
    [](AsyncWebServerRequest *request){
      request->send(404, "text/html", "Not found");
    }
  );


  this->server->on(
    "/",
    HTTP_GET,
    [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html);
    }
  );


  this->server->on(
    "/channel",
    HTTP_GET,
    [&](AsyncWebServerRequest *request){
      Serial.println("GET /channel - channel : " + String(this->channel));
      request->send(200, "text/html", String(this->channel));
    }
  );

  this->server->on(
    "/channel",
    HTTP_POST,
    [&](AsyncWebServerRequest *request){
      for (int i = 0; i < request->params(); i++) {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        if (p->name() == "channel") {
          this->channel = p->value().toInt();
        }
      }
      request->send(200, "text/html", "OK");
    }
  );


  this->server->on(
    "/files",
    HTTP_DELETE,
    [&](AsyncWebServerRequest *request){
      String result = "OK";
      for (int i = 0; i < request->params(); i++) {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        
        if (p->name() == "filename") {
          if (!LittleFS.remove(p->value().c_str())) {
            result = "NOK";
          }
        }
      }
      request->send_P(200, "text/html", result.c_str());
    }
  );



  this->server->on(
    "/files",
    HTTP_GET,
    [](AsyncWebServerRequest *request){
      Serial.println("GET /files ");
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      JsonArray file_list = json.createNestedArray("file_list");

      Dir dir = LittleFS.openDir("/");
      while (dir.next()) {
        JsonObject file_object = file_list.createNestedObject();
        file_object["filename"] = dir.fileName();
        file_object["size"] = 0;
        if(dir.fileSize()) {
            File f = dir.openFile("r");
            file_object["size"] = f.size();
            f.close();
        }
      }

      serializeJson(json, *response);
      request->send(response);
    }
  );


  this->server->on(
    "/info",
    HTTP_GET,
    [](AsyncWebServerRequest *request){
      Serial.println("GET /files ");
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(256);

        FSInfo fs_info;
        LittleFS.info(fs_info);

        json["totalBytes"] = fs_info.totalBytes;
        json["usedBytes"] = fs_info.usedBytes;
        json["freeBytes"] = fs_info.totalBytes - fs_info.usedBytes;

      serializeJson(json, *response);
      request->send(response);
    }
  );


  this->server->on(
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
        request->_tempFile = LittleFS.open("/" + filename, "w");
        Serial.println(logmessage);
      }

      if (len) {
        request->_tempFile.write(data, len);
        logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
        Serial.println(logmessage);
      }

      if (final) {
        logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
        request->_tempFile.close();
        Serial.println(logmessage);
      }
    }
  );
}

