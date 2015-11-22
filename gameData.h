/*gameData.h*/

class gameData{
  private:
    int gameID;
    char CFArray[6][7];
    gameData();
  public:
    gameData(int id): gameID(id);
    char[][] getArray();
    char getIndex(int r, int c){return CFArray[r][c]};
    int addPiece(int column);
}

