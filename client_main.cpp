#include <iostream>
#include "client.hpp"
#include "client_network.hpp"

#define BUFF_SIZE 56

using namespace std;

Client *client;
ClientNetwork *network;

void MoveEvent(int col) {
    network->SendMove(col);
}

int main(int argc, char *argv[]){

    string address = argv[1];
    string port = argv[2];
    client = new Client();
    client->InitializeScreen();
    client->SetMoveEvent(MoveEvent);

    network = new ClientNetwork(client, address, port);

    client->BeginGame();

    //Clean up!
    network->Close();
    endwin();
}
