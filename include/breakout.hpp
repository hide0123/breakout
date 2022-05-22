#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <stop_token>
#include <ncurses.h>

enum class Type {
    Ball,
    Paddle,
    Max
};

class Breakout {
public:
    Breakout();

    void loop(std::stop_token st);
    
    int getX(Type type);
    void setX(Type type, int x);

    std::string getPaddle();

private:
    int mx, my;
    int bx, by;
    int px, py;
    int dx, dy;
    int sx, sy;
    std::string paddle;
    std::vector<std::vector<bool>> blocks;

    void draw();
    bool move();
    void checkBlock();
    bool isBlock(int x, int y);
};