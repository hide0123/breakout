#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <stop_token>
#include <ncurses.h>

class Breakout {
public:
    Breakout();

    void loop(std::stop_token st);
    void checkKey();

private:
    int px;
    int mx, my;
    int bx, by;
    int dx, dy;
    int sx, sy;
    std::string paddle;
    std::vector<std::vector<bool>> blocks;

    void draw();
    bool move();
    void checkBlock();
    bool isBlock(int x, int y);
};