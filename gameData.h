/*gameData.h*/

#include <iostream>
#include <string>
class gameData{
  private:
    int gameID;
    char board[6][7];
    gameData(); //explicitly dissallow default constructor(cause I COMMAND IT!!!)
  public:
    gameData(int id): gameID(id);
    char[][] getArray();
    char getIndex(int r, int c){return board[r][c];}
    int addPiece(int column, char playerP);
    int getGameID(){return gameID;}
    string toString();
}

