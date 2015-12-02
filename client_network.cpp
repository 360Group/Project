#include "client_network.hpp"

#define BUFF_SIZE 56

int SetupTCPClientSocket(const char *host, const char *service);
void *RecvHandler(void *arg);

struct Pass{
    Client * client;
    int sock;
};

ClientNetwork::ClientNetwork(Client *client, string address, string port) {
    this->client = client;
    this->sockID = SetupTCPClientSocket(address.c_str(), port.c_str());

    if(this->sockID < 0) {
        this->client->Error("Error connecting to server: " + string(strerror(errno)));
        return;
    }
    Pass *pass = new Pass;
    pass->client = client;
    pass->sock = this->sockID;
    pthread_create(&this->recvThread, NULL, RecvHandler, (void *)pass);
}

void ClientNetwork::Close() {
    this->sendBuff = "quit";
    send(this->sockID, this->sendBuff.c_str(), this->sendBuff.length(), 0);
    close(this->sockID);
}

void ClientNetwork::SendMove(int col) {
    stringstream sstm;
    sstm << "move " << col;
    this->sendBuff = sstm.str();
    if(send(this->sockID, this->sendBuff.c_str(), this->sendBuff.length(), 0) != this->sendBuff.length()) {
        this->client->Error("Error connecting to server: " + string(strerror(errno)));
    }
}

void *RecvHandler(void *arg) {
    Pass p = *((Pass* )arg);
    int sockID = p.sock;
    Client *client = p.client;
    char buf[BUFF_SIZE];
    int readBytes;

    while(1) {
        readBytes = recv(sockID, buf, BUFF_SIZE - 1, 0);
        if(readBytes <= 0) {
            client->Error("Error receiving: " + string(strerror(errno)));
            break;
        }
        buf[readBytes] = '\0';
        string command(buf);
        if(command == "win") {
            client->Error("You win! Hit `q` to quit!");
            client->LockMovement();
        }
        else if(command == "lose") {
            client->Error("You lose! Hit `q` to quit!");
            client->LockMovement();
        }
        else if(command.substr(0,5) == "error") {
            client->Error("Error! " + command.substr(6));
        }
        else if(command.substr(0,10) == "boardState") {
            client->Error("                                                  ");
            char board[6][7];
            const char *str = command.substr(11).c_str();
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    char c = *(str + (i * 7) + j);
                    if (c == 'B') {
                        board[5-i][j] = 0;
                    }
                    else if (c == 'C') {
                        board[5-i][j] = 1;
                    }
                    else if (c == 'S') {
                        board[5-i][j] = 2;
                    }
                }
            }
            client->DrawToScreen(board);
        }
        else {
            client->Error("Recv: "+ command);
        }
    }

    return NULL;
}
