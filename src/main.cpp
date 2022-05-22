#include <ncurses.h>
#include <thread>
#include <functional>

#include "breakout.hpp"

void checkKey(Breakout &bo) {
    int x, key;

    while ((key = getch()) != 'q') {
        x = bo.getX(Type::Paddle);
        switch(key) {
            case KEY_LEFT:
                if(x > 0) {
                    bo.setX(Type::Paddle, x - 1);
                }
                break;
            case KEY_RIGHT:
                if(x < bo.getX(Type::Max) - bo.getPaddle().size()) {
                    bo.setX(Type::Paddle, x + 1);
                }
                break;
        }
    }
}

int main() {
    // ncurses settings
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    Breakout bo;
    std::jthread game(std::bind_front(&Breakout::loop, &bo));

    checkKey(bo);

    // End processing
    game.request_stop();
    endwin();
}