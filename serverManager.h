/*serverManager.h*/

//using namespace std;
#include <string>
#include "database.h"

class ServerManager{
  private:
    Database& datab;
    ServerManager(const ServerManager&);
    ServerManager& operator=(const ServerManager&);
    ServerManager():datab(Database::getInstance()){}
    ~ServerManager(){};
  public:
    static ServerManager& getInstance();
    std::string listGames();
    int joinGame(int gameID, std::string player);
    int makeNewGame(std::string p);
    //int quitGame(int id);
};
