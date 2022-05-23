#pragma once

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
    int mx, my; // max size
    int px = 10; // paddle size
    int bx = 0, by = 12; // ball position
    int dx = 1, dy = 1; // ball difference per frame
    int sx = 3, sy = 3; // space between walls and blocks

    const char* paddle = "--------";
    std::vector<std::vector<bool>> blocks;

    void draw();
    bool move();
    void checkBlock();
    bool isBlock(int x, int y);
};