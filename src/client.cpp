#include "client.h"
#include "crypto.h"
#include <vector>
// motmaen nistam ke in dorost bashe
// class Server;
#include "server.h"
#include <random>

Client::Client(std::string _id, const Server& _server)
    : id { _id }
    , server { &_server }
{
    std::cout << "Client Constructor" << std::endl;
    // std::string _public_key {}, _private_key {};
    crypto::generate_key(public_key, private_key);
    // public_key = _public_key;
    // private_key = _private_key;
}
std::string Client::get_id()
{
    return id;
}
std::string Client::get_publickey() const
{
    return public_key;
}
double Client::get_wallet()
{
    Server s = *this->server;
    // #include "server.h"
    double wallet_cl_standin = s.get_wallet(id);
    return wallet_cl_standin;
}
std::string Client::sign(std::string txt) const
{

    // check kon bebin doroste?
    // std::string signature = crypto::signMessage(private_key, "my data");
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}
bool Client::transfer_money(std::string receiver, double value)
{
    std::string trx_we_made {};
    trx_we_made += this->get_id();
    trx_we_made += "-";
    if (this->server->get_client(receiver) == nullptr) {
        return false;
    }
    trx_we_made += receiver;
    trx_we_made += "-";
    if (value > this->server->get_client(receiver)->get_wallet()) {
        return false;
    }
    trx_we_made += std::to_string(value);
    std::cout << trx_we_made;
    // motmaen nistam sign ro
    Server server_standin_cause_const = *this->server;
    server_standin_cause_const.add_pending_trx(trx_we_made, this->sign(trx_we_made));
    return 1;
}
size_t Client::generate_nonce()
{
    size_t numb_ret { 0 };
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 999999999);
    for (size_t i = 0; i < 2; i++) {

        numb_ret = static_cast<size_t>((dist(mt)));
    }
    return numb_ret;
}
