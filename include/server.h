#ifndef SERVER_H
#define SERVER_H
// khodam ina ro neveshtam motmaen nistam
#include "client.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
extern std::vector<std::string> pending_trxs;
// idk ke inja bayad tarif she

class Server {
public:
    Server() = default;
    // Server() const;
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id) const;
    double get_wallet(std::string id);
    static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
    bool add_pending_trx(std::string trx, std::string signature);
    size_t mine();
    friend void show_wallets(const Server& server);

private:
    std::map<std::shared_ptr<Client>, double> clients;
};

// ta inja

#endif // SERVER_H