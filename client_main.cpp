#include <iostream>
#include "client.hpp"
#include "client_network.hpp"

using namespace std;

int main(int argc, char *argv[]){

    string address = argv[1];
    string port = argv[2];
    Client *client = new Client();
    char board[7][6] = {
        {0,0,0,0,0,1},
        {0,0,0,0,2,2},
        {0,0,0,0,1,1},
        {0,0,0,2,2,2},
        {0,0,0,1,1,1},
        {0,0,2,2,2,2},
        {0,1,1,1,1,1}
    };
    client->SetBoard((char **)board);
    client->BeginGame();
    client->DrawToScreen();
    endwin();
    ClientNetwork *network = new ClientNetwork(client, address, port);
    network->SendMove(2000);
    network->Close();
}
