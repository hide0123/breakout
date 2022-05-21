#include <string>
#include <vector>

enum class Type {
    Ball,
    Paddle,
    Max
};

class Breakout {
public:
    Breakout();

    void loop();
    void finish();
    
    int getX(Type type);
    void setX(Type type, int x);

    std::string getPaddle();

private:
    bool playing;
    int mx, my;
    int bx, by;
    int px, py;
    int dx, dy;
    int sx, sy;
    std::string paddle;
    std::vector<std::vector<bool>> blocks;

    void draw();
    void move();
    void checkBlock();
    bool isBlock(int x, int y);
};