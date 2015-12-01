/*serverManager.h*/

class ServerManager{
  private:
    ServerManager(const ServerManager&);
    ServerManager& operator=(const ServerManager&);
    ServerManager();
    ~ServerManager();
  public:
    static ServerManager& getInstance();
    string listGames();
    int joinGame(int gameID, string player);
    int makeNewGame(sting p);
    int quitGame();
}
