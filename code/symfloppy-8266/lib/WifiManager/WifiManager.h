#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <configurations.h>
#include "../include/secrets.h"

class WifiManager {

    private:
        String mac_serial_truncated = "";
        bool is_connected = false;
        bool is_ap_started = false;
        bool is_connecting = false;

        unsigned long millis_duration_since_last_connected = 0;

    public:
        WifiManager();
        void init();
        void generateMacSerialTruncated();

        void startAccessPoint();
        void connect();
        void waitForConnection();
        void disconnect();
        void reconnect();
};
