#pragma once
#include <stdlib.h>

class MemMappedFile{
public:
    explicit MemMappedFile(int fd);
    ~MemMappedFile();

    MemMappedFile(const MemMappedFile& other) = delete;
    char* const get() const {return _ptr;}
private:
    size_t _len = 0;
    char* _ptr = nullptr;
    int _fd = 0;
};
