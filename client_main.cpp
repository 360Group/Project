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

    network = new ClientNetwork(client, address, port);

    client->SetMoveEvent(MoveEvent);

    char board[6][7] = {
        {1,2,1,2,1,2,1},
        {0,2,1,2,1,2,0},
        {0,0,1,2,1,0,0},
        {0,0,0,2,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
    };

    client->DrawToScreen(board);
    client->BeginGame();

    // char board2[6][7] = {
    //     {2,1,2,1,2,1,2},
    //     {0,1,2,1,2,1,0},
    //     {0,0,2,1,2,0,0},
    //     {0,0,0,1,0,0,0},
    //     {0,0,0,0,0,0,0},
    //     {0,0,0,0,0,0,0},
    // };
    // client->DrawToScreen(board2);
    // sleep(1);
    // while(1) {}
    //Clean up!
    network->Close();
    endwin();
}
