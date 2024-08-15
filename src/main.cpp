#include "OKXClient.h"
#include "Utils.h"
#include <iostream>

int main() {
    Json::Value config = Utils::readConfig("config/config.json");
    OKXClient client(config["api_key"].asString(), config["secret_key"].asString(), config["passphrase"].asString());

    std::string symbol = "MATIC-USDT-SWAP";
    std::string side = "buy";
    std::string type = "limit";
    double quantity = 1.0;

    std::string orderResponse = client.placeOrder(symbol, side, type, quantity);
    std::cout << "Order Response: " << orderResponse << std::endl;

    std::string orderbook = client.getOrderbook(symbol);
    std::cout << "Orderbook: " << orderbook << std::endl;

    std::string positions = client.getCurrentPositions();
    std::cout << "Current Positions: " << positions << std::endl;

    return 0;
}
