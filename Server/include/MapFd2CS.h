#ifndef MAP_FD_2_CS_H
#define MAP_FD_2_CS_H

#include "ClientStruct.h"
#include <memory>
#include <unordered_map>
#include <mutex>

class MapFd2CS
{
public:
    MapFd2CS() = delete;
    static bool addStruct(const int& clitFd);
    static bool getPStruct(const int& clitFd, std::shared_ptr<ClientStruct>& pCS);
    static void delStruct(const int& clitFd);
private:
    static std::mutex mt;
    static std::unordered_map<int, std::shared_ptr<ClientStruct>> mFC;
};

#endif