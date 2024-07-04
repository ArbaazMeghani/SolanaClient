#include <iostream>
#include <string>
#include <curl/curl.h>

// Solana RPC endpoint URL
const std::string rpcUrl = "https://api.devnet.solana.com";

// Callback function to handle data received from curl
size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *data)
{
    data->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // JSON-RPC request body
    std::string publicKey = "6GEMCtoaiPvxAPquih6HxcXy1UiN9K83ymtrMMbEkGpy";
    std::string jsonBody = "{\"jsonrpc\":\"2.0\", \"id\":1, \"method\":\"getBalance\", \"params\":[\"" + publicKey + "\"]}";

    // Initialize curl session
    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, rpcUrl.c_str());

        // Set POST method
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Set JSON-RPC request body
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());

        // Set headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set callback function to receive data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

        // Set data pointer to pass to callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // Print fetched data (balance)
            std::cout << "Balance response: " << std::endl;
            std::cout << readBuffer << std::endl;
        }

        // Cleanup curl
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
    {
        std::cerr << "Failed to initialize curl" << std::endl;
        return 1;
    }

    return 0;
}
