#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <ncurses.h>

class Client {
public:
    Client();
    ~Client();
    void SetBoard(char board[7][6]);
    void BeginGame();

private:
    char board[7][6];

    void DrawToScreen();
};
#endif
