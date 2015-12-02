/*gameData.cpp*/

#include "gameData.h"
#include "winCheck.h"

//Constructer used to make a new game
GameData::GameData(int id): gameID(id), player1("none"){
  board = new char*[6];
  for(int i=0; i < 6; i++){
    board[i] = new char[7];
  }
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      board[i][j] = 'B';
    }
  }
}

//Return the array of data
std::string GameData::getArray(){
  std::string array;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      array += board[i][j];
    }
  }
  return array;
}

/*Will try to add a piece to the column and will return an interger based on 
 * success
 * returns:
 * 0- move successful
 * 1- column is full and no more peices can be added
 * */
int GameData::addPiece(int column, char playerP){
  for(int i = 5; i >= 0; i--){
    if(board[i][column] == 'B'){
      board[i][column] = playerP;
      return 0;
    }
  }
  return 1;
} 

bool GameData::checkWin(){
  return winCheck(board);
}

/*return a string version of the array of the board*/
/*std::string GameData::toString(){
  std::string out;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      out.push_back(board[i][j]);
    }
  }
  return out;
}*/

//int main(){}
