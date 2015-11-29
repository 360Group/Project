/*database.cpp*/

#include "database.h"

Database::Database(): gameList(){
  //do nothing
}

Database& Database::getInstance(){
  static Database instance;
  return instance;
}

/*makes a new game and returns the gameID*/
int Database::newGame(){
  int size = gameList.size() + 1;
  gameList.push_back(new gameData(size));
  return size;
}

GameData Database::getGame(int id){
  
  for(int i=0;i < gameList.size(); i++){
    if(gameList[i].getID() == id)
      return gameList[i];
  }
}
