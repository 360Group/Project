/*Server for 3600 Project: Four Square Game
command line argument: ./serv [port]*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sstream>

#include "serverManager.h"

using namespace std;

void* HandleClient(void *client_sock);

int main(int argc, char* argv[]){
	int port;
	port = 5000;//atoi(argv[1]);

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

	int *client_sock;
  socklen_t length;

	struct sockaddr_in peer;

  //int param, retVal; //param and return values for thread

  for(;;){

    pthread_t thread;
    //int param, retVal;
	client_sock = new int;

	  if((*client_sock = accept(sock, (struct sockaddr*) &peer, &length)) < 0){
      cerr<< "bad accept()" << endl;
      return -1;
    }

    /*error here passing the socket*/
    pthread_create(&thread, NULL, HandleClient, (void *)client_sock);

    ///blerererererere
    //

    //pthread_join(thread, (void **)&retVal);

  }

  close(*client_sock);

}

void* HandleClient(void *client_sock){
  //things to print out message recieved, for testing
  char buffer[99999];
  int recvMsg;
  int csock = *((int *)client_sock);
  char player = 'C';

  int gameID; //id used to specify the game on the server you are playing

  //give client a new game
  gameID = ServerManager::getInstance().makeNewGame("client");
  //loop
  bool win = false;
  while(!win){
    //Database& mydata = Database.getInstance();
    //send game data to client
    //cerr << Database::getInstance().getGame(gameID).getArray() << endl;
    string toSend = "boardState " + Database::getInstance().getGame(gameID).getArray();;
    if(send(csock, toSend.c_str(), toSend.length(), 0) < 0){
      perror("send");
      cout << "error contancting client" << endl;
    }

    //wait for client move
    bool moved = false;
    while(!moved){
      memset(buffer, 0, 99999);
      recvMsg = recv(csock, buffer, 99999, 0);
      if(recvMsg < 0){
        perror("recv");
        cerr<< "bad recv()" << endl;
        //return -1;
      }
      else if(recvMsg == 0){
        cerr << "client disconnected" << endl;
	      return NULL;
      }
      else{
        string str(buffer);
        //cerr << str << endl;
      }
      //make move and respond if error
      string fromCl(buffer);
      if (strncmp(fromCl.c_str(), "quit", 4) == 0){
        cerr << "recieved quit" << endl;
        Database::getInstance().removeGame(gameID);
        moved = true;
        win = true;
	      return NULL;
      }
      else{
        int move = Database::getInstance().makeMove(fromCl, player, gameID);
        if(move == 0){
          moved = true;
        }else if(move == 1){
          string err = "error You cant put that there!!!";
          if(send(csock, err.c_str(), err.length(), 0) < 0){
            cout << "error contancting client" << endl;
          }
        }else{
          //Database::getInstance().removeGame(gameID);
          win = true;
          break;
        }
      }
    }

      //check for win
	if((win = Database::getInstance().getGame(gameID).checkWin())){
	string bsMsg = "boardState " +
		Database::getInstance().getGame(gameID).getArray();
	if(send(csock, bsMsg.c_str(), bsMsg.length(), 0) < 0){
	  perror("send");
	  cout << "error contancting client" << endl;
	}
	for(int sleeper=0; sleeper < 3000000; sleeper++) {}
    string winner = "win";
    if(send(csock, winner.c_str(), winner.length(), 0) < 0){
      cout << "error contancting client" << endl;
    }
  }

		// If client didn't win ai makes a move
	if( !win ){
		moved = false;
		int move = 1;
		int num;
		string myCL;
		stringstream myStream;
		while( !moved ){
			num = (rand() % 7);
			myStream << "move " << num;
			myCL = myStream.str();
			move = Database::getInstance().makeMove(myCL, 'S', gameID);
			if( move == 0 )
				moved = true;
		}
    win = Database::getInstance().getGame(gameID).checkWin();
		if(win){
		string bsMsg = "boardState " +
			Database::getInstance().getGame(gameID).getArray();
		if(send(csock, bsMsg.c_str(), bsMsg.length(), 0) < 0){
		  perror("send");
		  cout << "error contancting client" << endl;
		}
		for(int sleeper=0; sleeper < 3000000; sleeper++) {}
      string winner = "lose";
      if(send(csock, winner.c_str(), winner.length(), 0) < 0){
        cout << "error contancting client" << endl;
    }
    }
	}


  //end loop
  }
  return NULL;
  /*end actual code*/
}
