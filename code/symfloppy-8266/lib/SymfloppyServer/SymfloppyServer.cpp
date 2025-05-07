#include "SymfloppyServer.h"

SymfloppyServer::SymfloppyServer(int port) {
    this->server = new AsyncWebServer(port);
    this->channel = 12;
}


void SymfloppyServer::begin() {
    this->server->begin();
}


void SymfloppyServer::injectMidiFileManager(MidiFileManager * midi_file_manager) {
    this->midi_file_manager = midi_file_manager;
}


void SymfloppyServer::init() {

	this->server->onNotFound(
		[](AsyncWebServerRequest *request) {
			request->send(404, "text/html", "Not found");
		}
	);

	this->server->on(
		"/",
		HTTP_GET,
		[](AsyncWebServerRequest *request) {
			request->send_P(200, "text/html; charset=UTF-8", symfloppy_server_static_index_html);
		}
	);

	this->server->on(
		"/style.css",
		HTTP_GET,
		[](AsyncWebServerRequest *request) {
			request->send_P(200, "text/css; charset=UTF-8", symfloppy_server_static_style_css);
		}
	);

	this->server->on(
		"/index.js",
		HTTP_GET,
		[](AsyncWebServerRequest *request) {
			request->send_P(200, "application/javascript; charset=UTF-8", symfloppy_server_static_index_js);
		}
	);

	this->server->on(
		"/channel",
		HTTP_GET,
		[&](AsyncWebServerRequest *request) {
			Serial.println("GET /channel - channel : " + String(this->channel));
			request->send(200, "text/html", String(this->channel));
		}
	);

	
	this->server->on(
		"/channel",
		HTTP_POST,
		[&](AsyncWebServerRequest * request) {
			int value = 0;
			if (request->hasParam("channel", true)) {
				value = request->getParam("channel", true)->value().toInt();
			} else {
			  request->send(HTTP_CODE_BAD_REQUEST, "text/html", "Missing value");
			  return;
			}

			this->channel = value;
			request->send(200, "text/html", "OK");
		}
	);


	this->server->on(
		"/files",
		HTTP_DELETE,
		[&](AsyncWebServerRequest *request) {
			String result = "OK";
			if (request->hasParam("filename", true)) {
				String filename = request->getParam("filename", true)->value();
				if (!LittleFS.remove(filename)) {
					result = "NOK";
				}
			} else {
			  request->send(HTTP_CODE_BAD_REQUEST, "text/html", "Missing value");
			  return;
			}

			request->send_P(200, "text/html", result.c_str());
		}
	);


	// @todo: remove this old route when tested
	this->server->on(
		"/files-old",
		HTTP_DELETE,
		[&](AsyncWebServerRequest *request) {
			String result = "OK";
			for (int i = 0; i < request->params(); i++) {
				const AsyncWebParameter* p = request->getParam(i);
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
		[&](AsyncWebServerRequest *request) {
			Serial.println("GET /files-new ");
			AsyncResponseStream *response = request->beginResponseStream("application/json");
			DynamicJsonDocument json(1024);
			JsonArray file_list = json.createNestedArray("file_list");
			for (int i = 0; i < this->midi_file_manager->getFileCount(); i++) {
				const MidiFileManager::MidiFile* file = this->midi_file_manager->getFileAt(i);
				if (file) {
					JsonObject file_object = file_list.createNestedObject();
					file_object["filename"] = file->name;
					file_object["size"] = file->size;
				}
			}
			serializeJson(json, *response);
			request->send(response);
		}
	);


	this->server->on(
		"/info",
		HTTP_GET,
		[](AsyncWebServerRequest *request) {
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

