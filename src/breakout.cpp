#include <ncurses.h>
#include <thread>
#include <cmath>

#include "breakout.hpp"

Breakout::Breakout() : px(10), by(12), bx(0), dx(1), dy(1), sx(3), sy(3), playing(true), paddle("--------") {
    getmaxyx(stdscr, my, mx);
    blocks.resize(5);

    for(auto &row : blocks) {
        row.resize(mx - sx * 2);
    }
}

void Breakout::draw() {
    clear();
    getmaxyx(stdscr, my, mx);
    mvprintw(my - 1, px, paddle.c_str());
    mvprintw(by, bx, "O");

    for(int i = 0; i < blocks.size(); i++) {
        for(int j = 0; j < blocks.at(i).size(); j++) {
            if(!blocks.at(i).at(j)) {
                mvprintw(i + sy, j + sx, "#");
            }
        }
    }
    
    // Debug
    // mvprintw(0, mx - 15, "bx: %3d, by: %2d", bx, by);
    
    refresh();
}

bool Breakout::isBlock(int x, int y) {
    return x - sx >= 0 && x - sx < blocks.at(0).size() && y - sy >= 0 && y - sy < blocks.size() && !blocks.at(y - sy).at(x - sx);
}

void Breakout::checkBlock() {
    if(isBlock(bx + dx, by)) {
        blocks.at(by - sy).at(bx + dx - sx) = true;
        dx = -dx;
    }

    if(isBlock(bx, by + dy)) {
        blocks.at(by + dy - sy).at(bx - sx) = true;
        dy = -dy;
    }
}

void Breakout::move() {
    checkBlock();

    bx += dx;
    by += dy;

    if (bx < 0) {
        bx = 0;
        dx = std::abs(dx);
    }
    if (by < 0) {
        by = 0;
        dy = std::abs(dy);
    }
    if (bx > mx - 1) {
        bx = mx - 1;
        dx = -std::abs(dx);
    }
    if (by > my - 2 && bx > px - 1 && bx < px + paddle.length() + 1) {
        by = my - 2;
         dy = -std::abs(dy);
    } if (by > my) {
        finish();
    }
}

void Breakout::loop() {
    while(playing) {
        draw();
        move();
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    if (by > my) {
        char msg[] = "GAME OVER! (Press q to quit)";
        mvprintw(my/2, mx/2- (sizeof(msg)/2), "%s", msg);
        refresh();
    }
}

int Breakout::getX(Type type) {
    switch(type) {
        case Type::Ball:
            return bx;
        case Type::Paddle:
            return px;
        case Type::Max:
            return mx;
        default:
            return -1;
    }
}

void Breakout::setX(Type type, int x) {
    switch(type) {
        case Type::Ball:
            this->bx = x;
            break;
        case Type::Paddle:
            this->px = x;
            break;
        case Type::Max:
            this->mx = x;
            break;
        default:
            break;
    }
}

std::string Breakout::getPaddle() {
    return paddle;
}

void Breakout::finish() {
    playing = false;
}