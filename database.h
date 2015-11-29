/*database.h*/

#include "gamedata.h"
#include <vector>

class Database{
  private:
    std::vector<GameData> gameList;
    Database(const Database&);
    Database& operator=(const Database&);
    Database();
    ~Database();
  public:
    static Database& getInstance();
    string makeMove(string move);
    GameData getGame(int id)
    int newGame();

    
};
