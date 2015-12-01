#include "client.hpp"

#define START_BOARD 4
#define COL_OFF 6

Client::Client() {
    this->currentColSel = 0;
}

Client::~Client() {
    endwin();
}

void Client::SetMoveEvent(void (*event)(int)) {
    this->event = event;
}

void Client::InitializeScreen() {
    initscr();
    raw();
    clear(); //Clear the screen
    noecho(); //no echo, don't ouput keystrokes to terminal
    nonl(); //No newlines, lets up capture enter key
    curs_set(0); //Invisible cursor
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); //Player 1 color
    init_pair(2, COLOR_RED, COLOR_BLACK); //Player 2 color
    init_pair(3, COLOR_RED, COLOR_BLACK); //Error color
    printw("Use the left and right arrow keys or `j` and `k` to move the column\n");
    printw("Use `Enter` or the down arrow to select a column\n");
    printw("Use `q` to quit");
    refresh();
    mvprintw(START_BOARD+1,0,"");
    for(int i = 0; i < 6; i++) {
        printw(" +--------+--------+--------+--------+--------+--------+--------+\n");
        printw(" |        |        |        |        |        |        |        |\n");
    }
    printw(" +--------+--------+--------+--------+--------+--------+--------+");
}

void Client::BeginGame() {
    while (1) {
        mvprintw(START_BOARD, 6 + this->currentColSel * 9, "V");
        int ch  = getch();
        if(ch == KEY_LEFT || ch == 'j') {
            if(this->currentColSel > 0) {
                mvprintw(START_BOARD, COL_OFF + this->currentColSel * 9, " ");
                this->currentColSel--;
            }
        }
        else if(ch == KEY_RIGHT || ch == 'k') {
            if(this->currentColSel < 6) {
                mvprintw(START_BOARD, COL_OFF + this->currentColSel * 9, " ");
                this->currentColSel++;
            }
        }
        else if(ch == 13 || ch == KEY_DOWN) {
            if(this->event != NULL) {
                this->event(this->currentColSel);
            }
            //mvprintw(START_BOARD,0,"Down   ");
        }
        else if(ch == 'q') {
            break;
        }
        refresh();
    }
}

void Client::DrawToScreen(char board[6][7]) {
    for(int i = 0; i < 6; i++) {
        for(int j=0; j < 7; j++) {
            char token = board[i][j];
            if(token == 1) {
                attron(COLOR_PAIR(1));
                mvprintw((7 - i) * 2 + 2, j * 9 + COL_OFF, "O");
                attroff(COLOR_PAIR(1));
            }
            else if(token == 2) {
                attron(COLOR_PAIR(2));
                mvprintw((7 - i) * 2 + 2, j * 9 + COL_OFF, "O");
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

void Client::Error(string errorMsg) {
    attron(COLOR_PAIR(3));
    mvprintw(19, 3, errorMsg.c_str());
    attroff(COLOR_PAIR(3));
}
