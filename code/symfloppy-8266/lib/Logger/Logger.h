#pragma once

#include <Arduino.h>

#define logger Logger::getInstance()
#define LOG(msg) Logger::getInstance().println(msg)
#define LOG_PRINT(msg) Logger::getInstance().print(msg)


class Logger {

    private:
        Logger();
        bool enable_serial_print = true;

        void telnetPrint(String message);
        void serialPrint(String message);
        void serialPrintln(String message);
        
    public:
        void println(String message);
        void print(String message);
        static Logger& getInstance();

};
