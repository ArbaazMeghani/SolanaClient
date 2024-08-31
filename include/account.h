#pragma once

#include <string>
#include <cstdint>

struct Account
{
    std::string data;
    std::string owner;
    uint64_t lamports;
    uint64_t rentEpoch;
    bool executable;
    uint32_t space;
};