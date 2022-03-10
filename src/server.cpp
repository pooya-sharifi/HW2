#include "server.h"
#include "client.h"
#include <iostream>
#include <random>
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
        id += std::to_string(dist(mt));
        std::cout << id;
    }

    std::cout << "miyad in ja?3";
    std::shared_ptr<Client> pnt_client;
    Client khers(id, *this);
    //  inke id yeki bashan ro ham felan bikhiyal shodam!!****
    ////nemidoonam koodoome inast ya ziriye ya oonekiye
    pnt_client = std::make_shared<Client>(khers);
    // pnt_client->khers;
    // not sure at all?
    double wallet { 5.0 };
    clients[pnt_client] = wallet;
    return pnt_client;
}
std::shared_ptr<Client> Server::get_client(std::string id)
{
    // std::shared_ptr<Client> ptr_for;
    for (auto ptr_for = clients.begin(); ptr_for != clients.end(); ++ptr_for) {
        std::shared_ptr<Client> ptr_to_first;
        ptr_to_first = ptr_for->first;
        if (ptr_to_first->get_id() == id) {
            return ptr_to_first;
        }
    }

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
bool Server::parse_trx(std::string trx, std::string sender, std::string receiver, double value)
{
    // trx chiye?
    std::string string_trx;
    string_trx += sender;
    string_trx += "-";
    string_trx += receiver;
    string_trx += "-";
    string_trx += value;
    std::cout << string_trx;
}
bool Server::add_pending_trx(std::string trx, std::string signature)
{
}
size_t Server::mine()
{
}