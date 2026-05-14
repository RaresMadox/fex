#pragma once
#include <unistd.h>

class AutoFdClose{
private:
    int _fd;

public:
    AutoFdClose(int fd)
        :_fd(fd)
    {}

    ~AutoFdClose(){
        close(_fd);
    }

    int get(){
        return _fd;
    }
};