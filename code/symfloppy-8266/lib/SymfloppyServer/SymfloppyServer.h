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

        static constexpr int HTTP_CODE_OK = 200;
        static constexpr int HTTP_CODE_CREATED = 201;
        static constexpr int HTTP_CODE_BAD_REQUEST = 400;
        static constexpr int HTTP_CODE_NOT_FOUND = 404;
        static constexpr int HTTP_CODE_ERROR = 500;

        SymfloppyServer(int port);
        void init();
        void begin();

        void injectMidiFileManager(MidiFileManager * midi_file_manager);
};

#endif
