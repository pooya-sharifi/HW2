#include "server.h"
#include "client.h"
#include "crypto.h"
#include <iostream>
#include <random>
// #include <sstream>
#include <string>
// #include <vector>

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
    size_t count {};
    for (auto x : trx) {
        std::cout << "khers" << x << std::endl;
        if (x == '-') {
            count++;

            if (count == 1) {
                sender = word;
                word = "";
            }
            if (count == 2) {

                receiver = word;
                word = "";
            }

        } else {
            word += x;
        }
    }
    if (count == 1) {
        throw std::runtime_error(receiver);
    }
    if (count == 0) {
        throw std::runtime_error(sender);
    }
    auto value_standin = std::stod(word);
    value = value_standin;
    std::cout << sender << receiver << value;

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
    std::shared_ptr<Client> ptr_to_client;
    // std::shared_ptr<Client> ptr_to_map;
    auto _clients = this->clients;
    auto pointer_to_map = _clients.begin();
    auto pointer_to_first = pointer_to_map->first;
    // std::cout << this->clients;
    // std::cout << *ptr_to_map;
    // std::shared_ptr<Client> ptr_to_first;
    // std::string id_in_pending;
    // ptr_to_client = this->get_client(*ptr_to_first);
    if (bool authentic = crypto::verifySignature(pointer_to_first->get_publickey(), trx, signature) == 1) {
        return 1;
    } else {
        return 0;
    }
}
size_t Server::mine()
{
}