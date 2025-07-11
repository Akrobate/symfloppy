#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "ArduinoJson.h"
#include <LittleFS.h>

#include <configurations.h>
#include "../include/secrets.h"

class WifiManager {

    private:
        String mac_serial_truncated = "";
        String mdns_hostname = "symfloppy";
        
        bool is_connected = false;
        bool is_ap_started = false;
        bool is_connecting = false;
        bool is_configured_mdns = false;

        unsigned long millis_duration_since_last_connected = 0;

    public:
        WifiManager();
        void init();
        void generateMacSerialTruncated();

        bool saveWifiCredentials(const String& ssid, const String& password);
        bool connectWithSavedWifiCredentials();

        void startAccessPoint();
        void connect();
        void waitForConnection();
        void disconnect();
        void reconnect();

        void initMDNS();
        void updateMDNS();

};
