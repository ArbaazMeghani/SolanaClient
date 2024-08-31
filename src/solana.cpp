#include "solana.h"
#include <curl/curl.h>

Solana::Solana() : rpcUrl_("https://api.mainnet-beta.solana.com/"), curl_(NULL), headers_(NULL), parser_()
{
    initCurl();
}

Solana::Solana(const std::string &rpcUrl) : rpcUrl_(rpcUrl), curl_(NULL), headers_(NULL), parser_()
{
    initCurl();
}

void Solana::setRpcUrl(const std::string &rpcUrl)
{
    cleanupCurl();
    rpcUrl_ = rpcUrl;
    initCurl();
}

std::string Solana::getRpcUrl()
{
    return rpcUrl_;
}

size_t Solana::writeCallback(void *contents, size_t size, size_t nmemb, std::string *data)
{
    data->append((char *)contents, size * nmemb);
    return size * nmemb;
}

uint64_t Solana::getBalance(const std::string &publicKey)
{
    if (!curl_)
    {
        std::cerr << "curl not initialized" << std::endl;
        throw std::runtime_error("Curl not initialized");
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getBalance\", \"params\":[\"" + publicKey + "\"]}";

    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        throw std::runtime_error("Failed to get balance");
    }

    simdjson::dom::element element = parser_.parse(readBuffer);
    return element["result"]["value"].get_uint64().value();
}

std::string_view Solana::getLatestBlockhash()
{
    if (!curl_)
    {
        std::cerr << "curl not initialized" << std::endl;
        throw std::runtime_error("Curl not initialized");
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getLatestBlockhash\", \"params\":[]}";

    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        throw std::runtime_error("Failed to get recent blockhash");
    }

    simdjson::dom::element element = parser_.parse(readBuffer);
    return element["result"]["value"]["blockhash"].get_string().value();
}

Account Solana::getAccountInfo(const std::string &publicKey)
{
    if (!curl_)
    {
        std::cerr << "curl not initialized" << std::endl;
        throw std::runtime_error("Curl not initialized");
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getAccountInfo\", \"params\":[\"" + publicKey + "\"]}";

    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        throw std::runtime_error("Failed to get account info");
    }

    simdjson::dom::element element = parser_.parse(readBuffer);
    Account account;
    account.data = element["result"]["value"]["data"].get_string().value();
    account.owner = element["result"]["value"]["owner"].get_string().value();
    account.lamports = element["result"]["value"]["lamports"].get_uint64().value();
    account.rentEpoch = element["result"]["value"]["rentEpoch"].get_uint64().value();
    account.executable = element["result"]["value"]["executable"].get_bool().value();
    account.space = (uint32_t)element["result"]["value"]["space"].get_uint64().value();

    return account;
}

uint64_t Solana::getSlot()
{
    if (!curl_)
    {
        std::cerr << "curl not initialized" << std::endl;
        throw std::runtime_error("Curl not initialized");
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getSlot\", \"params\":[]}";

    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        throw std::runtime_error("Failed to get slot");
    }

    simdjson::dom::element element = parser_.parse(readBuffer);
    return element["result"].get_uint64().value();
}

std::string_view Solana::getSlotLeader()
{
    if (!curl_)
    {
        std::cerr << "curl not initialized" << std::endl;
        throw std::runtime_error("Curl not initialized");
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getSlotLeader\", \"params\":[]}";

    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        throw std::runtime_error("Failed to get slot leader");
    }

    simdjson::dom::element element = parser_.parse(readBuffer);
    return element["result"].get_string().value();
}

Solana::~Solana()
{
    cleanupCurl();
}

void Solana::initCurl()
{
    curl_ = curl_easy_init();
    if (!curl_)
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        throw std::runtime_error("Failed to initialize curl");
    }

    headers_ = curl_slist_append(headers_, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_URL, rpcUrl_.c_str());
    curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers_);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, Solana::writeCallback);
}

void Solana::cleanupCurl()
{
    curl_easy_cleanup(curl_);
    curl_slist_free_all(headers_);
    curl_ = NULL;
    headers_ = NULL;
}