#include <LittleFS.h>


class FileSystem {

    public:
        fs::FS * fs = nullptr;
        
        FileSystem();
        void init();

    private:

};
