#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

class Logger {
    
    public:

        static Logger * instance;

        static Logger *getInstance();

        void println(String data);
        void print(String data);

    private:
        Logger();
};

#endif
