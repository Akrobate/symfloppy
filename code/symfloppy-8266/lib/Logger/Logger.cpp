#include "Logger.h"

Logger::Logger() {
    // Exmpty
}


void Logger::println(String message) {
    if (this->enable_serial_print) {
        this->serialPrintln(message);
    }
}


void Logger::print(String message) {
    if (this->enable_serial_print) {
        this->serialPrint(message);
    }
}


void Logger::serialPrint(String message) {
    Serial.print(message);
}


void Logger::serialPrintln(String message) {
    Serial.println(message);
}


void Logger::telnetPrint(String message) {
    Serial.println(message);
}


Logger& Logger::getInstance() {
    static Logger instance;  // Initialisation thread-safe garantie en C++11+
    return instance;
}

