#include "client.hpp"

#define START_BOARD 4
#define COL_OFF 6

pthread_mutex_t screenLock = PTHREAD_MUTEX_INITIALIZER;

Client::Client() {
    this->currentColSel = 0;
    this->canMove = true;
}

Client::~Client() {
    endwin();
}

void Client::SetMoveEvent(void (*event)(int)) {
    if(this->canMove) {
        this->event = event;
    }
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
        pthread_mutex_lock(&screenLock);
        mvprintw(START_BOARD, 6 + this->currentColSel * 9, "V");
        pthread_mutex_unlock(&screenLock);
        int ch  = getch();
        if(ch == KEY_LEFT || ch == 'j') {
            if(this->currentColSel > 0 && this->canMove) {
                pthread_mutex_lock(&screenLock);
                mvprintw(START_BOARD, COL_OFF + this->currentColSel * 9, " ");
                pthread_mutex_unlock(&screenLock);
                this->currentColSel--;
            }
        }
        else if(ch == KEY_RIGHT || ch == 'k') {
            if(this->currentColSel < 6 && this->canMove) {
                pthread_mutex_lock(&screenLock);
                mvprintw(START_BOARD, COL_OFF + this->currentColSel * 9, " ");
                pthread_mutex_unlock(&screenLock);
                this->currentColSel++;
            }
        }
        else if(ch == 13 || ch == KEY_DOWN) {
            if(this->event != NULL && this->canMove) {
                this->event(this->currentColSel);
            }
            //mvprintw(START_BOARD,0,"Down   ");
        }
        else if(ch == 'q') {
            break;
        }
        pthread_mutex_lock(&screenLock);
        refresh();
        pthread_mutex_unlock(&screenLock);
    }
}

void Client::DrawToScreen(char board[6][7]) {
    pthread_mutex_lock(&screenLock);
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
    refresh();
    pthread_mutex_unlock(&screenLock);
}

void Client::Error(string errorMsg) {
    pthread_mutex_lock(&screenLock);
    attron(COLOR_PAIR(3));
    mvprintw(19, 3, (errorMsg + "                         ").c_str());
    attroff(COLOR_PAIR(3));
    refresh();
    pthread_mutex_unlock(&screenLock);
}

void Client::LockMovement() {
    this->canMove = false;
}
