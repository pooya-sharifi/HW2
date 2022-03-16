
#include "client.h"
#include "server.h"
#include <gtest/gtest.h>
#include <iostream>
// #include <vector>
// motmaen nistam inja jaye dorostiye ya na
void show_pending_transactions();
int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {

        Server panda;
        auto bryan { panda.add_client("bryan") };
        auto ali { panda.add_client("ali") };
        auto hassan { panda.add_client("hassan") };
        // std::cout << "public key by panda" << (bryan->get_publickey());
        // panda.add_pending_trx("bryan-hamed-2.2", bryan->sign("bryan-hamed-2.2"));
        // std::cout << bryan->generate_nonce();
        bryan->transfer_money("ali", 1.0);
        bryan->transfer_money("hassan", 1.0);
        bryan->transfer_money("hassan", 1.0);
        bryan->transfer_money("hassan", 1.0);
        bryan->transfer_money("ali", 1.0);
        panda.mine();
        show_wallets(panda);

        // std::string get_sign;
        // get_sign = bryan->sign("bryan - bryan1 - 2.0");
        // panda.add_pending_trx("bryan - bryan1 - 2.0", get_sign);
        // std::cout << bryan->get_id();
        // std::cout << bryan1->get_id();
        // std::cout << bryan->get_publickey();

        // // debug section
        // std::shared_ptr<Client> idk_justfor;
        // idk_justfor = panda.add_client("abs");
        // Server::add_client(a);
        // get_client();

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}
void show_pending_transactions()
{
    std::cout << std::string(20, '*') << std::endl;
    for (const auto& trx : pending_trxs)
        std::cout << trx << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}