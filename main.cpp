#include <iostream>
#include <string>
#include "solana.h"

int main()
{
    Solana solana("https://api.devnet.solana.com/");
    std::cout << solana.getBalance("6GEMCtoaiPvxAPquih6HxcXy1UiN9K83ymtrMMbEkGpy") << std::endl;
    std::cout << solana.getRecentBlockhash() << std::endl;
    return 0;
}
