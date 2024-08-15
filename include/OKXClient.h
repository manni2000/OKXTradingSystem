#ifndef OKXCLIENT_H
#define OKXCLIENT_H

#include <string>
#include <curl/curl.h>
#include <json/json.h>

class OKXClient {
public:
    // Constructor
    OKXClient(const std::string& apiKey, const std::string& secretKey, const std::string& passphrase);

    // Destructor
    ~OKXClient();

    // Public methods for trading
    std::string placeOrder(const std::string& symbol, const std::string& side, const std::string& type, double quantity);
    std::string cancelOrder(const std::string& orderId);
    std::string modifyOrder(const std::string& orderId, double newQuantity);
    std::string getOrderbook(const std::string& symbol);
    std::string getCurrentPositions();

private:
    // API credentials
    std::string apiKey;
    std::string secretKey;
    std::string passphrase;

    // Base URL for the API
    std::string baseUrl;

    // Private methods
    std::string sendRequest(const std::string& endpoint, const Json::Value& data);
    std::string signRequest(const std::string& timestamp, const std::string& method, const std::string& requestPath, const std::string& body);
};

#endif // OKXCLIENT_H
