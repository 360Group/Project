/*database.cpp*/

#include "database.h"

Database::Database(): gameList(){
  //do nothing
}

Database& Database::getInstance(){
  static Database instance;
  return instance;
}

/*return 0 if successful and 1 if error*/
int Database::makeMove(std::string move, char player, int id){
  std::string m;
  char n;
  int col;
  if(move[0] == 'm'){
    std::string::size_type pos;
    pos = move.find(' ',0);
    m = move.substr(0, pos);
    if(m.compare("move") == 0){
      n = move[5];
      col = n - '0';
      for(int i=0;i < gameList.size(); i++){
        if(gameList[i].getGameID() == id){
          //gameList[i].;
      
          if(gameList[i].addPiece(col, player) == 0)
            return 0;
          else
            return 1;
        }
      }
    }
  }
  else if(m.compare("quit") == 0){
    removeGame(id);
    return 2;
  }
}


/*makes a new game and returns the gameID*/
int Database::newGame(){
  int size = gameList.size() + 1;
  GameData newg(size);// = new GameData(size);
  gameList.push_back(newg/*new GameData(size)*/);
  return size;
}

void Database::removeGame(int id){
  std::vector<GameData>::iterator iter;// = gameList.begin();

  for(iter = gameList.begin(); iter != gameList.end(); iter++){
    if(iter->getGameID() == id){
      break;
    }
  }
  gameList.erase(iter);
  //gameList.shrink_to_fit();
}

GameData Database::getGame(int id){
  
  for(int i=0;i < gameList.size(); i++){
    if(gameList[i].getGameID() == id)
      return gameList[i];
  }
}

int Database::getListSize(){
  return gameList.size();
}



//int main(){}
