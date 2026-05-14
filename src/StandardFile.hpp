#pragma once
#include <string>
#include <filesystem>
#include <cstdio>

class StandardFile {
public:
    StandardFile(const std::string &path);
    bool        open(const char *mode = "rb");
    void        close();

    std::string readAll();
    bool        write(const std::string &data);

    static bool exists(const std::string &path);
private:
    std::string _path;
    FILE*       _handle = nullptr;
};
