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
			this->midi_file_manager->reload();
			request->send(HTTP_CODE_OK, "text/html", result);
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
			json["fs_total_bytes"] = fs_info.totalBytes;
			json["fs_used_bytes"] = fs_info.usedBytes;
			json["fs_free_bytes"] = fs_info.totalBytes - fs_info.usedBytes;
			json["free_heap"] = ESP.getFreeHeap();
			json["heap_fragmentation"] = ESP.getHeapFragmentation();
			json["max_free_block_size"] = ESP.getMaxFreeBlockSize();
			json["fps"] = this->fps;
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
		[&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {

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
				this->midi_file_manager->reload();
				Serial.println(logmessage);
			}
		}
	);

}

