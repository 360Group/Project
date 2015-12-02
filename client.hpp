#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <ncurses.h>
#include <iostream>

using namespace std;

class Client {
public:
    Client();
    ~Client();
    void BeginGame();
    void DrawToScreen(char board[6][7]);
    void Error(string errorMsg);
    void InitializeScreen();
    void SetMoveEvent(void (*event)(int));
    void LockMovement();

private:
    char currentColSel;
    void (*event)(int);
    bool canMove = true;
};
#endif
