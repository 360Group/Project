/*Server for 3600 Project: Four Square Game
command line argument: ./serv [port]*/

#include <iostream>
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
	int port;
	port = atoi(argv[1]);

	//setting up socket
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	//binding
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0){
		cout << "binding failed" << endl;
	}

	listen(sock, 256);

	int client_sock, length;

	struct sockaddr_in peer;

	client_sock = accept(sock, (struct sockaddr*) &peer, &length);
}
