#include <LittleFS.h>


class FileSystem {

    public:
        fs::FS * fs = nullptr;
        
        FileSystem();
        void init();
        fs::FS * getFS();

    private:
        bool is_inited = false;

};
