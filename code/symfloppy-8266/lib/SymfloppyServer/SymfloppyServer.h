#ifndef SymfloppyServer_h
#define SymfloppyServer_h

#include <ESPAsyncWebServer.h>

#include "AsyncJson.h"
#include "ArduinoJson.h"

#include <LittleFS.h>
#include <MidiFileManager.h>

#include "static/symfloppy_server_static_index_html.h"
#include "static/symfloppy_server_static_style_css.h"
#include "static/symfloppy_server_static_index_js.h"
// #include "static/round_timer_server_static_repository_js.h"



class SymfloppyServer {
    private:
        AsyncWebServer * server;
        MidiFileManager * midi_file_manager;

    public:
        int channel;

        SymfloppyServer(int port);
        void init();
        void begin();

        void injectMidiFileManager(MidiFileManager * midi_file_manager);
};

#endif
