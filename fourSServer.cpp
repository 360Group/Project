/*Server for 3600 Project: Four Square Game
command line argument: ./serv [port]*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* HandleClient(int client_sock);

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

	int client_sock;
  socklen_t length;

	struct sockaddr_in peer;

  int param, retVal; //param and return values for thread

  for(;;){

    pthread_t thread;
    //int param, retVal;

	  if((client_sock = accept(sock, (struct sockaddr*) &peer, &length)) < 0){
      cerr<< "bad accept()" << endl;
      return -1;
    }

    /*error here passing the socket*/
    pthread_create(&thread, NULL, HandleClient, (void *)&client_sock);

    ///blerererererere
    //

    pthread_join(thread, &retVal);

  }

  close(client_sock);

}

void *HandleClient(void *client_sock){
  char buffer[99999];
  int recvMsg;
  int csock;
  csock = (int)client_sock; 

  memset(buffer, 0, 99999);
  recvMsg = recv(csock, buffer, 99999, 0);
  if(recvMsg < 0){
    cerr<< "bad recv()" << endl;
    //return -1;
  }
  else if(recvMsg == 0){
    cerr << "client disconnected" << endl;
  }
  else{
    cerr << buffer << endl;
  }
}
