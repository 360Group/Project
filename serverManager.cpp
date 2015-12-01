/*serverManager.cpp*/

//#include <sstream>

static ServerManager& ServerManager::getInstance(){
  static ServerManager instance;
  return instance;
}

string ServerManager::listGames(){
  string games;
  int numGames = Database.getInstance().getListSize();
  const vector<GameData> list = Database.getInstance().getGameList();

  for(int i=0; i < numGames; i++){
     games += std::to_string(list[i].getID());
     games += '\n';
  }

  return games;
}

/*join an existing game and return the game ID if 
 * succeds and if not returns a -1*/
int ServerManager::joinGame(int gameID, string player){
  if(getGame(gameID).getPlayer().compare("none") == 0){
    getGame(gameID).addPlayer(player);
    return gameID;
  }
  else{
    return -1;
  }
}

/*makes new game and adds player to it
 * returns new games gameID*/
int ServerManager::makeNewGame(string p){
  int game = Database.newGame();
  joinGame(game, p);
  return game;
}

/*int ServerManager::quitGame(int id){
  
}*/
