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
    int mx, my; // max size
    int bx, by; // ball position
    int px = 0; // paddle position
    int dx = 1, dy = 1; // ball difference per frame
    int sx = 3, sy = 3; // space between walls and blocks

    int score = 0;
    int blockHeight = 5;

    const char* paddle = "--------";
    std::vector<std::basic_string<bool>> blocks;

    void draw();
    bool move();
    void checkBlock();
    bool isBlock(int x, int y);
};