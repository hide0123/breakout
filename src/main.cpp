#include <ncurses.h>
#include <thread>
#include <functional>

#include "breakout.hpp"

int main() {
    // ncurses settings
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    Breakout bo;
    std::jthread game(std::bind_front(&Breakout::loop, &bo));

    bo.checkKey();

    // End processing
    game.request_stop();
    endwin();
}