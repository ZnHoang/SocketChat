#include "MapFd2CS.h"

std::mutex mt;
std::unordered_map<int, std::shared_ptr<ClientStruct>> mFC;

bool MapFd2CS::addStruct(const int& clitFd)
{
    std::unique_lock<std::mutex> lk(mt);
    if(mFC.find(clitFd) != mFC.end())
    {
        return false;
    }
    auto pCS{std::make_shared<ClientStruct>(clitFd)};
    mFC[clitFd] = pCS;
    return true;
}

bool MapFd2CS::getPStruct(const int& clitFd, std::shared_ptr<ClientStruct>& pCS)
{
    std::unique_lock<std::mutex> lk(mt);
    if(mFC.find(clitFd) == mFC.end())
    {
        return false;
    }
    pCS.reset(mFC[clitFd].get());
    return true;
}

void MapFd2CS::delStruct(const int& clitFd)
{
    std::unique_lock<std::mutex> lk(mt);
    mFC.erase(clitFd);
}