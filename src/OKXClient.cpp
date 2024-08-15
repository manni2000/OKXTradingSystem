#include <iomanip>
#include "OKXClient.h"
#include "Utils.h"
#include <iostream>
#include <curl/curl.h>
#include <ctime>
#include <sstream>
#include <algorithm>

OKXClient::OKXClient(const std::string& apiKey, const std::string& secretKey, const std::string& passphrase)
    : apiKey(apiKey), secretKey(secretKey), passphrase(passphrase) {
    Json::Value config = Utils::readConfig("config/config.json");
    baseUrl = config["base_url"].asString();
}

OKXClient::~OKXClient() {}

std::string OKXClient::placeOrder(const std::string& symbol, const std::string& side, const std::string& type, double quantity) {
    Json::Value data;
    data["symbol"] = symbol;
    data["side"] = side;
    data["type"] = type;
    data["quantity"] = quantity;
    return sendRequest("/api/v5/trade/order", data);
}

std::string OKXClient::cancelOrder(const std::string& orderId) {
    Json::Value data;
    data["orderId"] = orderId;
    return sendRequest("/api/v5/trade/cancel-order", data);
}

std::string OKXClient::modifyOrder(const std::string& orderId, double newQuantity) {
    Json::Value data;
    data["orderId"] = orderId;
    data["quantity"] = newQuantity;
    return sendRequest("/api/v5/trade/amend-order", data);
}

std::string OKXClient::getOrderbook(const std::string& symbol) {
    return sendRequest("/api/v5/market/books?symbol=" + symbol, Json::Value());
}

std::string OKXClient::getCurrentPositions() {
    return sendRequest("/api/v5/account/positions", Json::Value());
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Handle memory problem
        return 0;
    }
    return newLength;
}

std::string OKXClient::sendRequest(const std::string& endpoint, const Json::Value& data) {
    std::string url = baseUrl + endpoint;
    std::string method = "POST";  // Assuming POST for this example, could be GET, etc.
    std::string body = Json::writeString(Json::StreamWriterBuilder(), data);
    std::string timestamp = std::to_string(std::time(nullptr));

    std::string signature = signRequest(timestamp, method, endpoint, body);  // Replace this with a simpler alternative if not needed

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Content-Type: application/json"));
    headers = curl_slist_append(headers, ("OK-ACCESS-KEY: " + apiKey).c_str());
    headers = curl_slist_append(headers, ("OK-ACCESS-SIGN: " + signature).c_str());
    headers = curl_slist_append(headers, ("OK-ACCESS-TIMESTAMP: " + timestamp).c_str());
    headers = curl_slist_append(headers, ("OK-ACCESS-PASSPHRASE: " + passphrase).c_str());

    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return response;
}

// Modified signRequest method to avoid OpenSSL usage
std::string OKXClient::signRequest(const std::string& timestamp, const std::string& method, const std::string& requestPath, const std::string& body) {
    // Simple hash or concatenation as a placeholder
    std::string prehash = timestamp + method + requestPath + body;

    // Placeholder for the signature, this should be replaced with an actual signing logic if needed
    std::hash<std::string> hasher;
    size_t hashValue = hasher(prehash);
    
    std::stringstream ss;
    ss << std::hex << hashValue;
    
    return ss.str();
}
