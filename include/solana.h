#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>

class Solana
{
public:
    Solana();
    Solana(const std::string &rpcUrl);
    void setRpcUrl(const std::string &url);
    ~Solana();
    std::string getRpcUrl();
    std::string getBalance(const std::string &publicKey);
    // std::string transfer(const std::string &from, const std::string &to, const std::string &amount);
    // std::string createAccount();
    // std::string createToken(const std::string &mintAuthority, const std::string &freezeAuthority);
    // std::string mintToken(const std::string &mintAuthority, const std::string &to, const std::string &amount);
    // std::string transferToken(const std::string &from, const std::string &to, const std::string &amount);
    // std::string getAccountInfo(const std::string &publicKey);
    // std::string getTokenAccountInfo(const std::string &publicKey);
    // std::string getMintInfo(const std::string &publicKey);
    // std::string getRecentBlockhash();
    // std::string createAndTransfer(const std::string &from, const std::string &to, const std::string &amount);
    // std::string createAndTransferToken(const std::string &from, const std::string &to, const std::string &amount);
    // std::string createAndTransferTokenWithAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority);
    // std::string createAndTransferTokenWithAuthorityAndFreezeAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority);
    // std::string createAndTransferTokenWithAuthorityAndFreezeAuthorityAndMintAuthority(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority, const std::string &mintAuthority);
    // std::string createAndTransferTokenWithAuthorityAndFreezeAuthorityAndMintAuthorityAndToken(const std::string &from, const std::string &to, const std::string &amount, const std::string &authority, const std::string &freezeAuthority, const std::string &mintAuthority, const std::string &token = "");

private:
    // CURL *curl;
    std::string rpcUrl_;
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *data);
};