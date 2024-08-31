#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <simdjson.h>
#include "account.h"

class Solana
{
public:
    Solana();
    Solana(const std::string &rpcUrl);
    void setRpcUrl(const std::string &url);
    ~Solana();
    std::string getRpcUrl();
    uint64_t getBalance(const std::string &publicKey);
    Account getAccountInfo(const std::string &publicKey);
    std::string_view getLatestBlockhash();
    uint64_t getSlot();
    std::string_view getSlotLeader();
    std::vector<std::string_view> getSlotLeaders(uint64_t startSlot, uint64_t limit);

private:
    CURL *curl_;
    struct curl_slist *headers_;
    std::string rpcUrl_;
    simdjson::dom::parser parser_;
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *data);
    void initCurl();
    void cleanupCurl();
};