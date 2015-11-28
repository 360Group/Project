/*database.h*/

#include "gamedata.h"

class Database{
  private:
    std::vector<gameData> gameList;
    Database(const Database&);
    Database& operator=(const Database&);
    Database();
    ~Database();
  public:
    static Database& getInstance();
    string makeMove(string move);

    
};
