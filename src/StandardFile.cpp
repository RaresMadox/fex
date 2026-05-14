#include "StandardFile.hpp"

StandardFile::StandardFile(const std::string &path)
    : _path(path)
{}

bool StandardFile::open(const char *mode) {
    _handle = fopen(_path.c_str(), mode);
    return _handle != nullptr;
}

void StandardFile::close() {
    if (_handle) {
        fclose(_handle);
        _handle = nullptr;
    }
}

std::string StandardFile::readAll() {
    if (!_handle) return {};

    fseek(_handle, 0, SEEK_END);
    long size = ftell(_handle);
    fseek(_handle, 0, SEEK_SET);

    std::string buffer(size, '\0');
    fread(buffer.data(), 1, size, _handle);
    return buffer;
}

bool StandardFile::write(const std::string &data) {
    if (!_handle) return false;
    return fwrite(data.data(), 1, data.size(), _handle) == data.size();
}

bool StandardFile::exists(const std::string &path) {
    return std::filesystem::exists(path);
}
