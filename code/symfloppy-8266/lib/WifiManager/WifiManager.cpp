#include "WifiManager.h"

WifiManager::WifiManager() {
    // Constructor implementation
}

void WifiManager::init() {
    
}

void WifiManager::generateMacSerialTruncated() {
    String mac_serial = WiFi.macAddress();
    mac_serial.replace(":","");
    this->mac_serial_truncated = mac_serial.substring(0, 4);  
}

void WifiManager::startAccessPoint() {
    delay(1000); // To test if is required
    this->generateMacSerialTruncated();
    String ssid = "SYMFLOPPY_" + this->mac_serial_truncated;
    WiFi.softAP(ssid.c_str());
    // Serial.println("Access Point started with SSID: " + ssid);
}


void WifiManager::connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    this->waitForConnection();
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

void WifiManager::disconnect() {
    WiFi.disconnect(true, false); 
    WiFi.mode(WIFI_OFF);
}


void WifiManager::reconnect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    this->waitForConnection();
}


// SHould implement max tries
void WifiManager::waitForConnection() {
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
}


bool WifiManager::saveWifiCredentials(const String& ssid, const String& password) {
    DynamicJsonDocument doc(512);
    doc["ssid"] = ssid;
    doc["password"] = password;

    File file = LittleFS.open("/credentials.json", "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write JSON to file");
        file.close();
        return false;
    }
    return true;
}


bool WifiManager::connectWithSavedWifiCredentials() {

    File file = LittleFS.open("/credentials.json", "r");
    if (!file) {
        Serial.println("No saved WiFi credentials found");
        return false;
    }
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        Serial.println("Failed to parse saved WiFi credentials");
        return false;
    }
    String ssid = doc["ssid"];
    String password = doc["password"];
    if (ssid.isEmpty() || password.isEmpty()) {
        Serial.println("Saved WiFi credentials are empty");
        return false;
    }
    Serial.println("Connecting with saved WiFi credentials...");
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    this->waitForConnection();
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}