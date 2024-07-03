#include "base58.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>

const std::array<int8_t, 128> Base58::indexMap = []
{
    std::array<int8_t, 128> map{};
    std::fill(map.begin(), map.end(), -1);
    for (size_t i = 0; i < alphabet.size(); ++i)
    {
        map[static_cast<unsigned char>(alphabet[i])] = static_cast<int8_t>(i);
    }
    return map;
}();

std::string Base58::encode(const std::string &input)
{
    if (input.empty())
        return "";

    // Convert the input string to a vector of bytes
    std::vector<unsigned char> bytes(input.begin(), input.end());

    // Count leading zeros
    int leadingZeros = 0;
    for (unsigned char byte : bytes)
    {
        if (byte == 0)
        {
            ++leadingZeros;
        }
        else
        {
            break;
        }
    }

    // Convert byte vector to base58
    std::vector<unsigned char> base58;
    base58.reserve(bytes.size() * 138 / 100 + 1); // log(256) / log(58), rounded up

    for (unsigned char byte : bytes)
    {
        int carry = byte;
        for (auto it = base58.begin(); it != base58.end(); ++it)
        {
            carry += 256 * (*it);
            *it = carry % 58;
            carry /= 58;
        }
        while (carry > 0)
        {
            base58.push_back(carry % 58);
            carry /= 58;
        }
    }

    // Add leading zeros
    for (int i = 0; i < leadingZeros; ++i)
    {
        base58.push_back(0);
    }

    // Convert base58 values to a string
    std::string encoded;
    encoded.reserve(base58.size());
    for (auto it = base58.rbegin(); it != base58.rend(); ++it)
    {
        encoded += alphabet[*it];
    }

    return encoded;
}

std::string Base58::decode(const std::string &input)
{
    if (input.empty())
        return "";

    // Convert the input string to a vector of base58 values
    std::vector<unsigned char> input58;
    for (char c : input)
    {
        int8_t value = indexMap[static_cast<size_t>(c)];
        if (value == -1)
        {
            throw std::invalid_argument("Invalid character in Base58 string");
        }
        input58.push_back(value);
    }

    // Count leading zeros
    int leadingZeros = 0;
    for (char c : input)
    {
        if (c == alphabet[0])
        {
            ++leadingZeros;
        }
        else
        {
            break;
        }
    }

    // Convert base58 vector to bytes
    std::vector<unsigned char> bytes((input58.size() * 733 / 1000) + 1); // log(58) / log(256), rounded up
    for (unsigned char value : input58)
    {
        int carry = value;
        for (auto it = bytes.rbegin(); it != bytes.rend(); ++it)
        {
            carry += 58 * (*it);
            *it = carry % 256;
            carry /= 256;
        }
    }

    // Remove leading zeros
    auto it = std::find_if(bytes.begin(), bytes.end(), [](unsigned char c)
                           { return c != 0; });
    std::vector<unsigned char> result(it, bytes.end());

    // Add leading zeros
    result.insert(result.begin(), leadingZeros, 0);

    // Convert bytes to a string
    return std::string(result.begin(), result.end());
}
