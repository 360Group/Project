#ifndef CLIENT_NETWORK_HPP
#define CLIENT_NETWORK_HPP
#include "client.hpp"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include <sstream>
#include <errno.h>

using namespace std;

class ClientNetwork {
    public:
        ClientNetwork(Client *client, string address, string port);
        void Close();
        void SendMove(int col);

    private:
        Client *client;
        int sockID;
        string sendBuff;
        pthread_t recvThread;

        static void *RecvHandler(void *arg);
};
#endif
