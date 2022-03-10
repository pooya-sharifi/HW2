#include "client.h"
#include "crypto.h"
#include <vector>
// motmaen nistam ke in dorost bashe
// class Server;
#include "server.h"

Client::Client(std::string _id, const Server& _server)
    : id { _id }
    , server { &_server }
{

    std::cout << "Client Constructor" << std::endl;
    std::string _public_key {}, _private_key {};
    crypto::generate_key(_public_key, _private_key);
    public_key = _public_key;
    private_key = _private_key;
}
std::string Client::get_id()
{
    return id;
}
std::string Client::get_publickey()
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
std::string Client::sign(std::string txt)
{

    // check kon bebin doroste?
    // std::string signature = crypto::signMessage(private_key, "my data");
    // return signature;
}
bool Client::transfer_money(std::string receiver, double value)
{
}
size_t Client::generate_nonce()
{
}