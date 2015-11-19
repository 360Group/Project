#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <ncurses.h>

using namespace std;

class Client {
public:
    Client();
    ~Client();
    void SetBoard(char **board);
    void BeginGame();
    void DrawToScreen();
    void Error(string errorMsg);

private:
    char **board;
};
#endif
