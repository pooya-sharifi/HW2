#ifndef SERVER_H
#define SERVER_H
// khodam ina ro neveshtam motmaen nistam
#include "client.h"
#include <map>
#include <memory>
// #include <sstream>
#include <string>
// #include <vector>

class Server {
public:
    Server() = default;
    // Server() const;
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id) const;
    double get_wallet(std::string id);
    bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
    bool add_pending_trx(std::string trx, std::string signature);
    size_t mine();

private:
    std::map<std::shared_ptr<Client>, double> clients;
};

// ta inja

#endif // SERVER_H