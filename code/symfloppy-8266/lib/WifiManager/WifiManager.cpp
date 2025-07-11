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

    // String ssid = "SYMFLOPPY_" + this->mac_serial_truncated;
    // WiFi.softAP(ssid.c_str());
    WiFi.softAP(WIFI_ACCESS_POINT_SSID, WIFI_ACCESS_POINT_PASSWORD);
    Serial.println("Access Point started with SSID: " + String(WIFI_ACCESS_POINT_SSID) + " and Password: " + String(WIFI_ACCESS_POINT_PASSWORD));
}


void WifiManager::connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting");
    this->waitForConnection();
    Serial.println("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    this->initMDNS();

}

void WifiManager::disconnect() {
    WiFi.disconnect(true, false); 
    WiFi.mode(WIFI_OFF);
}


void WifiManager::reconnect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    this->waitForConnection();
    this->initMDNS();
}


void WifiManager::waitForConnection() {
    int attempts = 0;
    const int max_attempts = 20;
    while (WiFi.status() != WL_CONNECTED && attempts < max_attempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    this->is_connected = (WiFi.status() == WL_CONNECTED);
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
    Serial.print("Connecting...");
    this->waitForConnection();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}


void WifiManager::initMDNS() {
    if (MDNS.begin(this->mdns_hostname)) {
        this->is_configured_mdns = true;
        Serial.println("mDNS configured");
    } else {
        this->is_configured_mdns = false;
        Serial.println("mDNS error");
    }
}


void WifiManager::updateMDNS() {
    if (this->is_configured_mdns) {
        if (!MDNS.isRunning()) {
            this->initMDNS();
        }
        MDNS.update();
    }
}
