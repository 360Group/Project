/*gameData.h*/

#include <iostream>
#include <string>

class GameData{
  private:
    int gameID;
    char board[6][7];
    std::string player1; //player from client
    //char player2; //AI
    GameData(); //explicitly dissallow default constructor(cause I COMMAND IT!!!)
  public:
    GameData(int id);
    std::string getArray();
    char getIndex(int r, int c){return board[r][c];}
    int addPiece(int column, char playerP);
    int getGameID(){return gameID;}
    std::string toString();
    std::string getPlayer(){return player1;}
    void addPlayer(std::string name){player1 = name;}
};

