#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <configurations.h>
#include "../include/secrets.h"

class WifiManager {

    private:
        String mac_serial_truncated = "";

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
