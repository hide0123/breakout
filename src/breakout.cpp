#include "breakout.hpp"

Breakout::Breakout() {
    getmaxyx(stdscr, my, mx);

    bx = px + sizeof(paddle) / 2;
    by = my - 2;
    
    blocks.assign(blockHeight, std::basic_string<bool>(mx - sx * 2, true));
}

void Breakout::draw() {
    clear();
    getmaxyx(stdscr, my, mx);
    mvprintw(my - 1, px, paddle);
    mvprintw(by, bx, "O");
    mvprintw(0, 0, "Score: %d", score);

    for(int i = 0; i < blocks.size(); i++) {
        for(int j = 0; j < blocks.at(i).size(); j++) {
            if(blocks.at(i).at(j)) {
                mvprintw(i + sy, j + sx, "#");
            }
        }
    }
    
    // Debug
    // mvprintw(0, mx - 15, "bx: %3d, by: %2d", bx, by);
    
    refresh();
}

bool Breakout::isBlock(int x, int y) {
    x -= sx;
    y -= sy;

    return x >= 0 && x < blocks.at(0).size() && y >= 0 && y < blocks.size() && blocks.at(y).at(x);
}

void Breakout::checkBlock() {
    // x
    if(isBlock(bx + dx, by)) {
        blocks.at(by - sy).at(bx + dx - sx) = false;
        dx = -dx;
        score++;
    }

    // y
    if(isBlock(bx, by + dy)) {
        blocks.at(by + dy - sy).at(bx - sx) = false;
        dy = -dy;
        score++;
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
    if (by > my - 2 && bx > px - 1 && bx < px + sizeof(paddle) + 1) {
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
        mvprintw(my / 2, mx / 2 - (sizeof(msg) / 2), "%s", msg);
        refresh();
    }
}

void Breakout::checkKey() {
    int key;

    while ((key = getch()) != 'q') {
        switch(key) {
            case KEY_LEFT: if(px > 0) px--; break;
            case KEY_RIGHT: if(px < mx - sizeof(paddle)) px++; break;
        }
    }
}