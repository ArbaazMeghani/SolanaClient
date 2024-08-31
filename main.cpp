#include <iostream>
#include <string>
#include "solana.h"

int main()
{
    Solana solana("https://api.devnet.solana.com/");
    std::string publicKey = "6GEMCtoaiPvxAPquih6HxcXy1UiN9K83ymtrMMbEkGpy";
    std::cout << solana.getBalance(publicKey) << std::endl;
    std::cout << solana.getLatestBlockhash() << std::endl;

    Account account = solana.getAccountInfo(publicKey);
    std::cout << "Account info for public key: " << publicKey << std::endl;
    std::cout << "data: " << account.data << std::endl;
    std::cout << "owner: " << account.owner << std::endl;
    std::cout << "lamports: " << account.lamports << std::endl;
    std::cout << "rentEpoch: " << account.rentEpoch << std::endl;
    std::cout << "executable: " << account.executable << std::endl;
    std::cout << "space: " << account.space << std::endl;

    std::cout << "Current slot: " << solana.getSlot() << std::endl;
    std::cout << "Slot leader: " << solana.getSlotLeader() << std::endl;

    std::cout << "Slot leaders: " << std::endl;
    std::vector<std::string_view> slotLeaders = solana.getSlotLeaders(solana.getSlot(), 10);
    for (const auto &slotLeader : slotLeaders)
    {
        std::cout << slotLeader << std::endl;
    }

    std::cout << "Block height: " << solana.getBlockHeight() << std::endl;
    return 0;
}
