#include "MemMappedFile.hpp"
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

MemMappedFile::MemMappedFile(int fd)
    :_fd(fd)
{
    struct stat sb;
    if(fstat(fd,&sb)){
        return;
    }
    _len = sb.st_size;
    _ptr = (char *)mmap(NULL,_len,PROT_READ,MAP_PRIVATE,_fd,0);
}

MemMappedFile::~MemMappedFile()
{
    munmap(_ptr,_len);
    _ptr = nullptr;
    _len = 0;
    _fd = 0;
}


