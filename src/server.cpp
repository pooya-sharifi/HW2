#include "server.h"
#include "client.h"
#include "crypto.h"
#include <iostream>
#include <random>
// #include <sstream>
#include <string>
// #include <vector>
std::vector<std::string> pending_trxs;
std::shared_ptr<Client> Server::add_client(std::string id)
{
    int flag { 0 };
    for (auto ptr_for = clients.begin(); ptr_for != clients.end(); ++ptr_for) {
        std::shared_ptr<Client> ptr_to_first;
        ptr_to_first = ptr_for->first;
        if (ptr_to_first->get_id() == id) {
            flag = 1;
            std::cout << flag;
        }
    }
    std::string id_for_changes { id };
    if (flag == 1) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, 9);
        for (size_t i { 0 }; i != 4; i++) {
            id_for_changes = id_for_changes + std::to_string(static_cast<int>((dist(mt))));
        }
    }

    std::shared_ptr<Client> pnt_client;
    Client khers(id_for_changes, *this);
    pnt_client = std::make_shared<Client>(khers);
    double wallet { 5.0 };
    clients[pnt_client] = wallet;
    return pnt_client;
}
std::shared_ptr<Client> Server::get_client(std::string id) const
{
    std::shared_ptr<Client> ptr_for_return { nullptr };
    for (auto ptr_for = clients.begin(); ptr_for != clients.end(); ++ptr_for) {
        std::shared_ptr<Client> ptr_to_first;
        ptr_to_first = ptr_for->first;
        if (ptr_to_first->get_id() == id) {
            ptr_for_return = ptr_to_first;
            return ptr_for_return;
        }
    }
    return ptr_for_return;
}
double Server::get_wallet(std::string id)
{
    for (auto ptr_for = clients.begin(); ptr_for != clients.end(); ++ptr_for) {
        std::shared_ptr<Client> ptr_to_first;
        ptr_to_first = ptr_for->first;
        if (ptr_to_first->get_id() == id) {
            double wallet_standin;
            wallet_standin = ptr_for->second;
            return wallet_standin;
        }
    }
    throw std::runtime_error("no wallet found");
}
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::string word {};
    std::string word1 {};
    std::string word2 {};
    size_t count {};
    for (auto x : trx) {
        if (x == '-') {
            count++;

            if (count == 1) {
                word1 = word;
                word = {};
            }
            if (count == 2) {

                word2 = word;
                word = {};
            }

        } else {
            word += x;
        }
    }
    // std::cout << word;
    // std::cout << "after loop...." << std::endl;
    if (count == 1) {
        throw std::runtime_error(receiver);
    }
    if (count == 0) {
        throw std::runtime_error(sender);
    }
    // std::cout << "after if...." << std::endl;

    auto value_standin = std::stod(word);
    // std::cout << "after stod...." << std::endl;
    value = value_standin;
    sender = word1;
    receiver = word2;
    // std::cout << "after value...." << std::endl;
    // std::cout << sender << std::endl;
    // std::cout << receiver << std::endl;
    // std::cout << value << std::endl;
    return 1;
}
bool Server::add_pending_trx(std::string trx, std::string signature)
{
    std::string sender {}, receiver {};
    double value;
    this->parse_trx(trx, sender, receiver, value);
    auto pointer_to_sender { (this->get_client(sender)) };
    auto publickey_given { pointer_to_sender->get_publickey() };
    std::cout << "public key by " << publickey_given;
    bool authentic = crypto::verifySignature(publickey_given, trx, signature);
    if (value > this->get_client(receiver)->get_wallet()) {
        return false;
    }
    if (authentic == 1) {
        pending_trxs.push_back(trx);

        std::cout << trx;
        std::cout << pending_trxs[0];
        return 1;
    } else {
        return 0;
    }
}
size_t Server::mine()
{
    std::string mempool {};
    size_t rows = pending_trxs.size();
    for (size_t i = 0; i < rows; i++) {
        mempool += pending_trxs[i];
        std::cout << "ina ke mibini mempoole" << mempool << std::endl;
    }
    size_t nonce_generated {};
    std::shared_ptr<Client> ptr_for_return { nullptr };
    size_t flag { 0 };
    while (flag == 0) {
        for (auto ptr_for = clients.begin(); ptr_for != clients.end(); ++ptr_for) {
            std::string mempool_standin { mempool };
            std::shared_ptr<Client> ptr_to_first;
            ptr_to_first = ptr_for->first;
            nonce_generated = ptr_to_first->generate_nonce();
            mempool_standin += std::to_string(nonce_generated);
            std::cout << "mempool baade nonce" << mempool_standin << std::endl;
            std::string hash { crypto::sha256(mempool_standin) };
            // std::cout << hash << "this was hash" << std::endl;
            if (hash.substr(0, 10).find("000") != std::string::npos) {
                std::cout << "Miner is  ";
                std::cout << ptr_to_first->get_id() << std::endl;
                std::cout << "MIners wallet before :" << this->get_client(ptr_to_first->get_id())->get_wallet() << std::endl;
                clients[ptr_to_first] = (this->get_client(ptr_to_first->get_id())->get_wallet()) + 6.25;
                std::cout << ptr_to_first->get_id();
                std::cout << "MIners wallet after Mine:" << this->get_client(ptr_to_first->get_id())->get_wallet() << std::endl;
                flag = 1;
                mempool = mempool_standin;
                if (flag == 1) {
                    for (size_t i = 0; i < rows; i++) {
                        std::string sender {}, receiver {};
                        double value;
                        Server::parse_trx(pending_trxs[i], sender, receiver, value);
                        // std::cout << "this is the sender of the transaction" << sender << std::endl;
                        // std::cout << "this is transactions being done:wallet of the sender:" << this->get_client(sender)->get_wallet() << std::endl;
                        clients[this->get_client(sender)] = (this->get_client(sender)->get_wallet()) - value;
                        // std::cout << "done:sender" << sender << std::endl;
                        // std::cout << "done sender wallet:" << (this->get_client(sender)->get_wallet()) << std::endl;
                        clients[this->get_client(receiver)] = (this->get_client(receiver)->get_wallet()) + value;
                        // std::cout << "done:reciver" << receiver << std::endl;
                        // std::cout << "done reciver wallet:" << (this->get_client(receiver)->get_wallet()) << std::endl;
                    }
                    pending_trxs.clear();
                    return nonce_generated;
                }
            }
        }
    }
    throw std::runtime_error("couldnt mine");
}
void show_wallets(const Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for (const auto& client : server.clients)
        std::cout << client.first->get_id() << " : " << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}
