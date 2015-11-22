/*gameData.cpp*/

#include "gameData.h"

//Constructer used to make a new game
gameData(int id){
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      board[i][j] = 'B';
    }
  }
}

//Return the array of data
char[][] getArray(){
  return board;
}

/*Will try to add a piece to the column and will return an interger based on 
 * success
 * returns:
 * 0- move successful
 * 1- column is full and no more peices can be added
 * */
int addPiece(int column, char playerP){
  for(int i = 5; i >= 0; i--){
    if(board[i][column] == 'B'){
      board[i][column] = playerP;
      return 0;
    }
  }
  return 1;
} 

/*return a string version of the array of the board*/
string toString(){
  string out;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      out.push_back(board[i][j]);
    }
  }
  return out;
}
