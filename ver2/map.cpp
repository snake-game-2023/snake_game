#include "map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    map.resize(height);
    for (int i = 0; i < height; i++) {
        map[i].resize(width);
    }
    for (int i = 0; i < height; i++) {
        for (int j=0; j < width; j++) {
            map[i][j] = 0;
        }
    }
}


void Map::setWall(int y, int x) {
    map[y][x] = 1;
}

void Map::setImmuneWall(int y, int x) {
    map[y][x] = 2;
}

void Map::setGate(int y, int x) {
    map[y][x] = 3;
}

void Map::setItem(int y, int x) {
    map[y][x] = 4;
}

void Map::setPoison(int y, int x) {
    map[y][x] = 5;
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

void Map::setWidth(int width) {
    this->width = width;
}   

void Map::setHeight(int height) {
    this->height = height;
}

void Map::draw(WINDOW* win) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            switch (getObject(i, j)) {
                case 0:
                    init_pair(1, COLOR_WHITE, COLOR_WHITE);
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win, i, j, " ");
                    wattroff(win, COLOR_PAIR(1));
                    break;
                case 1:
                    init_pair(2, COLOR_BLACK, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(2));
                    mvwprintw(win, i, j, "#");
                    wattroff(win, COLOR_PAIR(2));
                    break;
                case 2:
                    init_pair(3, COLOR_BLUE, COLOR_BLUE);
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win, i, j, "X");
                    wattroff(win, COLOR_PAIR(3));
                    break;
                case 3: 
                    init_pair(4, COLOR_CYAN, COLOR_BLUE);
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, i, j, "G");
                    wattroff(win, COLOR_PAIR(4));
                    break;
                case 4:
                    init_pair(5, COLOR_WHITE, COLOR_GREEN);
                    wattron(win, COLOR_PAIR(5));
                    mvwprintw(win, i, j, "I");
                    wattroff(win, COLOR_PAIR(5));
                    break;
                case 5:
                    init_pair(6, COLOR_BLACK, COLOR_RED);
                    wattron(win, COLOR_PAIR(6));
                    mvwprintw(win, i, j, "P");
                    wattroff(win, COLOR_PAIR(6));
                    break;
                case 6:
                    mvwprintw(win, i, j, "S");
                    break;
            }
        }
    }
}

void Map::makeGate() {
    //immune wall 제외한 곳에 gate를 하나만 생성
    int y, x;
    x = rand() % (width-1) ;
    y = rand() % (height-1) ;

    if(map[y][x] == 0 || map[y][x] == 1) {
        map[y][x] = 3;
    } else {
        makeGate();
    }
}

void Map::makeItem() {
    //빈 공간에 item을 하나만 생성
    int y, x;
    x = (rand() % (width-2)) + 1;
    y = (rand() % (height-2)) + 1;

    if(map[y][x] == 0) {
        map[y][x] = 4;
    } else {
        makeItem();
    }
}

void Map::makePoison() {
    //빈 공간에 poison을 하나만 생성
    int y, x;
    x = rand() % (width-2) + 1;
    y = rand() % (height-2) + 1;

    if(map[y][x] == 0) {
        map[y][x] = 5;
    } else {
        makePoison();
    }
}

void Map::makeWall() {
    //map의 가장자리에 wall을 생성
    for (int i=0; i<height; i++) {
        map[i][0] = 1;
        map[i][width-1] = 1;
    }
    for (int i=0; i<width; i++) {
        map[0][i] = 1;
        map[height-1][i] = 1;
    }
}

void Map:: makeSnake(int y, int x){
    map[y][x] = 6;
}

void Map::makeImmuneWall() {
    map[0][0] = 2;
    map[0][width-1] = 2;
    map[height-1][0] = 2;
    map[height-1][width-1] = 2;
}

bool Map::isCollusion(int y, int x, int point) {
    return map[y][x] == point;
}

int Map::getObject(int y, int x) {
    return map[y][x];
}

pair<int, int> Map::getPoint(int y, int x) {
    pair<int, int> tmp = make_pair(y, x);
    return tmp;
}

void Map::setObject(int y, int x, int point) {
    map[y][x] = point;
}