#include "client.hpp"

Client::Client() {

}

Client::~Client() {

}

void Client::BeginGame() {
    initscr();
    printw("Hello World!");
    refresh();
    getch();
    endwin();
}
