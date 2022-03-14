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
    // std::shared_ptr<Client> ptr_for;
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
        // ham 4 ta bayad bashe ,ham int nemidoonam chera nemishe
        //  id_for_changes=id+dist(mt)+dist(mt)+dist(mt)+dist(mt);
        for (size_t i { 0 }; i != 4; i++) {
            id_for_changes = id_for_changes + std::to_string(static_cast<int>((dist(mt))));
        }
        // std::cout << id;
    }

    // std::cout << "miyad in ja?3";
    std::shared_ptr<Client> pnt_client;
    Client khers(id_for_changes, *this);
    //  inke id yeki bashan ro ham felan bikhiyal shodam!!****
    ////nemidoonam koodoome inast ya ziriye ya oonekiye
    pnt_client = std::make_shared<Client>(khers);
    // pnt_client->khers;
    // not sure at all?
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
    // in ro bara vaghti mishe ke esme pointer ba id yeki bashe
    // std::shared_ptr<Client> ret;
    // ret = make_shared<Client>(id);
    // return id;
    // // kamel kon !!!!!???
    // std::shared_ptr<Client> pnt_client;
    // std::string id_standin;

    // std::cout << khers.get_id();
    // return pnt_client;
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
}
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::string word {};
    std::string word1 {};
    std::string word2 {};
    size_t count {};
    for (auto x : trx) {
        std::cout << "khers" << x << std::endl;
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
    std::cout << word;
    std::cout << "after loop...." << std::endl;
    if (count == 1) {
        throw std::runtime_error(receiver);
    }
    if (count == 0) {
        throw std::runtime_error(sender);
    }
    std::cout << "after if...." << std::endl;

    auto value_standin = std::stod(word);
    std::cout << "after stod...." << std::endl;
    value = value_standin;
    sender = word1;
    receiver = word2;
    std::cout << "after value...." << std::endl;
    std::cout << sender << std::endl;
    std::cout << receiver << std::endl;
    std::cout << value << std::endl;
    return 1;
    // trx chiye?
    // std::string string_trx;
    // string_trx += sender;
    // string_trx += "-";
    // string_trx += receiver;
    // string_trx += "-";
    // string_trx += value;
    // std::cout << string_trx;
}
bool Server::add_pending_trx(std::string trx, std::string signature)
{
    std::string sender {}, receiver {};
    double value;
    this->parse_trx(trx, sender, receiver, value);
    auto khers = (this->get_client(sender));
    auto mongol = khers->get_publickey();
    std::cout << "public key by khers" << mongol;
    bool authentic = crypto::verifySignature(mongol, trx, signature);

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
            std::cout << hash << "this was hash" << std::endl;
            if (hash[63] == '0' && hash[62] == '0' && hash[61] == '0') {
                std::cout << "khers was victorius";
                flag = 1;
                return flag;
            }
        }
    }
}