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
    stringstream sstm;
    sstm << "Socket: " << this->sockID;
    this->client->Error(sstm.str());
    sleep(1);
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
    stringstream sstm;
    sstm << "Receiving thread active: " << sockID;

    char buf[BUFF_SIZE];
    int readBytes;
    client->Error(sstm.str());

    while(1) {
        readBytes = recv(sockID, buf, BUFF_SIZE - 1, 0);
        if(readBytes <= 0) {
            sleep(1);
            client->Error("Error receiving: " + string(strerror(errno)));
            break;
        }
        buf[readBytes] = '\0';
        string command(buf);
        if(command == "win") {
            client->Error("You win!");
        }
        else if(command == "lose") {
            client->Error("You lose!");
        }
        else if(command.substr(0,5) == "error") {
            client->Error("Error! " + command.substr(6));
        }
        else if(command.substr(0,10) == "boardState") {
            char[6][7] board;
            char *str = command.substr(11).c_str();
            for(int i = 0; i < 7; i++) {
                for(int j = 0; j < 6; j++) {
                    
                }

            }
        }
        else {
            client->Error("Recv: "+ command);
        }
    }

    return NULL;
}
