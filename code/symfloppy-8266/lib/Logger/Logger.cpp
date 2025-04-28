#include "Logger.h"

Logger * Logger::instance = nullptr;

void Logger::println(String data) {
    Serial.println(data);
}

void Logger::print(String data) {
    Serial.print(data);
}
