#include "solana.h"
#include <curl/curl.h>

Solana::Solana() : rpcUrl_("https://api.mainnet-beta.solana.com/")
{
}

Solana::Solana(const std::string &rpcUrl) : rpcUrl_(rpcUrl)
{
}

void Solana::setRpcUrl(const std::string &rpcUrl)
{
    rpcUrl_ = rpcUrl;
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

std::string Solana::getBalance(const std::string &publicKey)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        return "";
    }

    CURLcode res;
    std::string readBuffer;
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getBalance\", \"params\":[\"" + publicKey + "\"]}";

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set URL
    curl_easy_setopt(curl, CURLOPT_URL, Solana::rpcUrl_.c_str());

    // Set POST method
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Set JSON-RPC request body
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());

    // Set headers
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set callback function to receive data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Solana::writeCallback);

    // Set data pointer to pass to callback function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    // Cleanup curl
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return readBuffer;
}

Solana::~Solana()
{
}