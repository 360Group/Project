#include "client.hpp"

Client::Client() {
    this->currentColSel = 0;
}

Client::~Client() {

}

void Client::BeginGame() {
    initscr();
    raw();
    clear(); //Clear the screen
    noecho(); //no echo, don't ouput keystrokes to terminal
    nonl(); //No newlines, lets up capture enter key
    curs_set(0); //Invisible cursor
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    printw("Use the left and right arrow keys or `j` and `k` to move the column");
    mvprintw(1,0,"Use `Enter` or the down arrow to select a column");
    refresh();
    DrawToScreen();
    while (1) {
        mvprintw(3, 2 + this->currentColSel * 9, "V");
        int ch  = getch();
        if(ch == KEY_LEFT || ch == 'j') {
            if(this->currentColSel > 0) {
                mvprintw(3, 2 + this->currentColSel * 9, " ");
                this->currentColSel--;
            }
        }
        else if(ch == KEY_RIGHT || ch == 'k') {
            if(this->currentColSel < 6) {
                mvprintw(3, 2 + this->currentColSel * 9, " ");
                this->currentColSel++;
            }
        }
        else if(ch == 13 || ch == KEY_DOWN) {
            mvprintw(3,0,"Down   ");
        }
        else if(ch ==  KEY_F(5) || ch == 'q') {
            break;
        }
        //mvprintw(3, 0, "Col: %d, %d ", this->currentColSel, 2 + this->currentColSel * 9);
        refresh();
    }
}

void Client::DrawToScreen() {
    for(int i = 0; i < 6; i++) {
        for(int j=0; j < 7; j++) {
            char token = this->board[i][j];
            //printw("Token: %d\n", token);
            if(token == 0) {
                mvprintw((7 - i) * 2 + 2, j * 9 + 2, "0");
                continue;
            }
            else if(token == 1) {
                attron(COLOR_PAIR(1));
                mvprintw((7 - i) * 2 + 2, j * 9 + 2, "X");
                attroff(COLOR_PAIR(1));
            }
            else if(token == 2) {
                attron(COLOR_PAIR(2));
                mvprintw((7 - i) * 2 + 2, j * 9 + 2, "X");
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

void Client::SetBoard(char board[6][7]) {
    for(int i=0; i < 6; i++) {
        for(int j=0; j < 7; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}
