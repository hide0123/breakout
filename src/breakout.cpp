#include "breakout.hpp"

Breakout::Breakout() : px(10), by(12), bx(0), dx(1), dy(1), sx(3), sy(3), paddle("--------") {
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

bool Breakout::move() {
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
    if (by > my - 2 && bx > px - 1 && bx < px + paddle.size() + 1) {
        by = my - 2;
         dy = -std::abs(dy);
    } if (by > my) {
        return false;
    }
    return true;
}

void Breakout::loop(std::stop_token st) {
    while(!st.stop_requested()) {
        draw();

        if(!move()) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    if (by > my) {
        char msg[] = "GAME OVER! (Press q to quit)";
        mvprintw(my/2, mx/2- (sizeof(msg)/2), "%s", msg);
        refresh();
    }
}

void Breakout::checkKey() {
    int key;

    while ((key = getch()) != 'q') {
        switch(key) {
            case KEY_LEFT: if(px > 0) px--; break;
            case KEY_RIGHT: if(px < mx - paddle.size()) px++; break;
        }
    }
}