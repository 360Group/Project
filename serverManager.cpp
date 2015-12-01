/*serverManager.cpp*/

#include <sstream>
#include "serverManager.h"
//#include "database.h"
//using namespace std;


ServerManager& ServerManager::getInstance(){
  static ServerManager instance;
  return instance;
}

/*std::string ServerManager::listGames(){
  std::string games;
  std::stringstream convert;
  int numGames = datab.getInstance().getListSize();
  const std::vector<GameData> list = datab.getInstance().getGameList();

  for(int i=0; i < numGames; i++){
     convert << list[i].getGameID() << std::endl;
  }
  games = convert.str();
  return games;
}*/

/*join an existing game and return the game ID if 
 * succeds and if not returns a -1*/
int ServerManager::joinGame(int gameID, std::string player){
  if(datab.getInstance().getGame(gameID).getPlayer().compare("none") == 0){
    datab.getInstance().getGame(gameID).addPlayer(player);
    return gameID;
  }
  else{
    return -1;
  }
}

/*makes new game and adds player to it
 * returns new games gameID*/
int ServerManager::makeNewGame(std::string p){
  int game = datab.getInstance().newGame();
  joinGame(game, p);
  return game;
}

/*int ServerManager::quitGame(int id){
  
}*/

//int main(){}
