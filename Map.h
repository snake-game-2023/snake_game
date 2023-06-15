#include "Snake.h"
#include "Wall.h"

class Map {
    private:
    int width, height;
    Snake snake;
    Wall wall;

    public:
    Map(int width, int height);
    void draw();
    void collusion();
    void update();
    void input();
    void run();
};