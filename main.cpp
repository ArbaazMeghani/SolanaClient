#include <iostream>
#include <string>
#include "base58.h"

int main()
{
    std::string test = "test";
    std::string encoded = Base58::encode(test);
    std::string decoded = Base58::decode("3yZe7d");
    std::cout << "Original: " << test << std::endl;
    std::cout << "Encoded: " << encoded << std::endl;
    std::cout << "Decoded: " << decoded << std::endl;
    return 0;
}
