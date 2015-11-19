#include <iostream>
#include "client.hpp"
#include "client_network.hpp"

using namespace std;

int main(int argc, char *argv[]){

    string address = argv[1];
    string port = argv[2];
    Client *client = new Client();
    char board[6][7] = {
        {1,2,1,2,1,2,1},
        {0,2,1,2,1,2,0},
        {0,0,1,2,1,0,0},
        {0,0,0,2,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
    };
    client->SetBoard(board);
    client->BeginGame();
    //client->DrawToScreen();
    // getch();
    endwin();
    ClientNetwork *network = new ClientNetwork(client, address, port);
    network->SendMove(2000);
    network->Close();
}
