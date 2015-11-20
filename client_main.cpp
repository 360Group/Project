#include <iostream>
#include "client.hpp"
#include "client_network.hpp"

using namespace std;

Client *client;
ClientNetwork *network;

void MoveEvent(int col) {
    cout << col << " ";
    //network->SendMove(col);
}

int main(int argc, char *argv[]){

    string address = argv[1];
    string port = argv[2];
    client = new Client();
    network = new ClientNetwork(address, port);

    client->SetMoveEvent(MoveEvent);
    network->SetClient(client);

    char board[6][7] = {
        {1,2,1,2,1,2,1},
        {0,2,1,2,1,2,0},
        {0,0,1,2,1,0,0},
        {0,0,0,2,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
    };

    client->InitializeScreen();
    client->DrawToScreen(board);
    client->BeginGame();

    network->SendMove(2000);
    network->Close();
    delete client;
    delete network;
}
