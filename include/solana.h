#pragma once

#include <iostream>
#include <string>

class Solana
{
public:
    static void setRpcUrl(const std::string &url);
    static std::string getRpcUrl();
    static std::string getBalance(const std::string &publicKey);
    // static std::string transfer(const std::string &from, const std::string &to, const std::string &amount);
    // static std::string createAccount();
    // static std::string createToken(const std::string &mintAuthority, const std::string &freezeAuthority);
    // static std::string mintToken(const std::string &mintAuthority, const std::string &to, const std::string &amount);
    // static std::string transferToken(const std::string &from, const std::string &to, const std::string &amount);
    // static std::string getAccountInfo(const std::string &publicKey);
    // static std::string getTokenAccountInfo(const std::string &publicKey);
    // static std::string getMintInfo(const std::string &publicKey);
    // static std::string getRecentBlockhash();
    // static std::string createAndTransfer(const std::string &from, const std::string &to, const std::string &amount);
    // static std::string createAndTransferToken(const std::string &from, const std::string &to, const std::string &amount);
    // static std::string createAndTransferTokenWithAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority);
    // static std::string createAndTransferTokenWithAuthorityAndFreezeAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority);
    // static std::string createAndTransferTokenWithAuthorityAndFreezeAuthorityAndMintAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority, const std::string &mintAuthority);
    // static std::string createAndTransferTokenWithAuthorityAndFreezeAuthorityAndMintAuthorityAndToken(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority, const std::string &mintAuthority, const std::string &token = "");

private:
    static std::string rpcUrl_;
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *data);
};