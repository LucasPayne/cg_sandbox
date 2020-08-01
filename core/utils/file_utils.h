/*--------------------------------------------------------------------------------
    Header-only module for convenient operations with files.
--------------------------------------------------------------------------------*/
#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <time.h>

typedef std::vector<uint8_t> ByteArray;

//reference: https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
struct stat stat_file(const std::string &path)
{
    struct stat stat_buffer;
    int return_code = stat(path.c_str(), &stat_buffer);
    if (return_code != 0) {
        fprintf(stderr, "ERROR: Failed to stat file \"%s\".\n", path.c_str());
        exit(EXIT_FAILURE);
    }
    return stat_buffer;
}

size_t file_size(const std::string &path)
{
    return stat_file(path).st_size;
}
// Returns POSIX time in seconds.
time_t file_last_modification_time(const std::string &path)
{
    return stat_file(path).st_mtime;
}

bool load_bytes_from_file(const std::string &path, ByteArray &bytes)
{
    size_t size = file_size(path);
    bytes = ByteArray(size);
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);
    if (!file.is_open()) return false;
    file.read((char *) &bytes[0], size);
    file.close();
    return true;
}

#endif // FILE_UTILS_H
