#include "client.hpp"

Client::Client() {

}

Client::~Client() {

}

void Client::BeginGame() {
    initscr();
    raw();
    clear();
    noecho();
    nonl();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    printw("Use the left and right arrow keys or `j` and `k` to move the column");
    mvprintw(1,0,"Use `Enter` or the down arrow to select a column");
    refresh();
    while (1) {
        int ch  = getch();
        if(ch == KEY_LEFT || ch == 'j') {
            mvprintw(3,0,"Left   ");
        }
        else if(ch == KEY_RIGHT || ch == 'k') {
            mvprintw(3,0,"Right   ");
        }
        else if(ch == 13 || ch == KEY_DOWN) {
            mvprintw(3,0,"Down   ");
        }
        else if(ch ==  KEY_F(5) || ch == 'q') {
            break;
        }
        refresh();
    }
}

void Client::DrawToScreen() {
    for(int i = 0; i < 7; i++) {
        for(int j=0; j < 6; j++) {
            char token = this->board[i][j];
            if(token == 0) {
                return;
            }
            else if(token == 1) {
                attron(COLOR_PAIR(1));
                mvprintw(i * 3, j * 3, "X");
                attroff(COLOR_PAIR(1));
            }
            else if(token == 2) {
                attron(COLOR_PAIR(2));
                mvprintw(i * 3, j * 3, "X");
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

void Client::SetBoard(char **board) {
    this->board = board;
}
