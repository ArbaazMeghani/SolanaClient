#include <iostream>
#include <string>
#include "solana.h"

int main()
{
    Solana solana;
    std::cout << solana.getBalance("6GEMCtoaiPvxAPquih6HxcXy1UiN9K83ymtrMMbEkGpy") << std::endl;
    std::cout << solana.getBalance("6GEMCtoaiPvxAPquih6HxcXy1UiN9K83ymtrMMbEkGpy") << std::endl;
    return 0;
}
