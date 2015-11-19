#include <iostream>
#include "client.hpp"
#include "client_network.hpp"

using namespace std;

int main(int argc, char *argv[]){

    string address = argv[1];
    string port = argv[2];
    Client *client = new Client();
    client->BeginGame();
    ClientNetwork *network = new ClientNetwork(client, address, port);
    network->SendMove(2000);
    network->Close();
}
