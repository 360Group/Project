/*database.h*/

#include "gameData.h"
#include <vector>
#include <string>

class Database{
  private:
    std::vector<GameData> gameList;
    Database(const Database&);
    Database& operator=(const Database&);
    Database();
    ~Database(){};
  public:
    static Database& getInstance();
    int makeMove(std::string move, char player, int id);
    GameData getGame(int id);
    int newGame();
    void removeGame(int id);
    int getListSize();
    const std::vector<GameData> getGameList(){return gameList;}

    
};
