#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <ncurses.h>

using namespace std;

class Client {
public:
    Client();
    ~Client();
    void SetBoard(char board[6][7]);
    void BeginGame();
    void DrawToScreen();
    void Error(string errorMsg);

private:
    char board[6][7];
    char currentColSel;
};
#endif
