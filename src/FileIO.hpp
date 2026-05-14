#pragma once
#include <string>
#include <filesystem>
#include <cstdio>



typedef int (Closer)(FILE *);

template<typename Closer>
class FileIO {
public:
    FileIO(FILE *f)
        : _handle(f)
    {}

    ~FileIO(){
        if (_handle) {
            Closer _closer(_handle);
        }
    }

    FILE* get() {return _handle;};
    operator FILE*(){return _handle;}
private:
    FILE*       _handle = nullptr;
};
