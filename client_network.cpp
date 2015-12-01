#include "client_network.hpp"

#define BUFF_SIZE 56

int SetupTCPClientSocket(const char *host, const char *service);

ClientNetwork::ClientNetwork(string address, string port) {
    this->sockID = SetupTCPClientSocket(address.c_str(), port.c_str());
    if(this->sockID < 0) {
        cerr << "Error connecting to server" << endl;
        return;
    }
    pthread_create(&this->recvThread, NULL, RecvHandler, &this->sockID);
}

void ClientNetwork::Close() {
    this->sendBuff = "quit";
    cout << "SendBuff: " << this->sendBuff << endl;
    send(this->sockID, this->sendBuff.c_str(), this->sendBuff.length(), 0);
    close(this->sockID);
}

void ClientNetwork::SendMove(int col) {
    stringstream sstm;
    sstm << "move " << col;
    this->sendBuff = sstm.str();
    cout << "SendBuff: " << this->sendBuff << endl;
    send(this->sockID, this->sendBuff.c_str(), this->sendBuff.length(), 0);
}

void ClientNetwork::SetClient(Client *client) {
    this->client = client;
}

void *ClientNetwork::RecvHandler(void *arg) {
    int sockID = *((int*)arg);
    char buf[BUFF_SIZE];
    size_t readBytes;
    //printf("[Recv] Socket id: %d\n", sockID);

    while((readBytes = recv(sockID, buf, BUFF_SIZE - 1, 0))) {
        buf[readBytes] = '\0';
        printf("%s\n", buf);
    }

    return NULL;
}
