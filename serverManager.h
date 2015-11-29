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
    int joinGame();
    int startGame();
    int quitGame();
}
