#pragma once

#include <string>
#include <array>

class Base58
{
public:
    static std::string encode(const std::string &input);
    static std::string decode(const std::string &input);

private:
    static constexpr std::string_view alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    static const std::array<int8_t, 128> indexMap;
};