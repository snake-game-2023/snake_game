#include "snake.h"

Snake::Snake(int height, int width, Direction dir) {
    this->dir = dir;
    //add three body
    body.push_back(make_pair(2, 4));
    body.push_back(make_pair(2, 3));
    body.push_back(make_pair(2, 2));
    isDead = false;
}

void Snake::setDir(Direction dir) {
    this->dir = dir;
}

void Snake::draw(WINDOW* win) {
    init_pair(7, COLOR_GREEN, COLOR_GREEN);
    init_pair(8, COLOR_WHITE, COLOR_GREEN);
    
    for (auto p : body) {
        if (p == body.front()) {
            wattron(win, COLOR_PAIR(8));
            if (dir == UP) {
                    mvwprintw(win, p.first, p.second, "^");
                } else if (dir == DOWN) {
                    mvwprintw(win, p.first, p.second, "v");
                } else if (dir == LEFT) {
                    mvwprintw(win, p.first, p.second, "<");
                } else if (dir == RIGHT) {
                    mvwprintw(win, p.first, p.second, ">");
                }
                wattroff(win, COLOR_PAIR(8));
            } else {
                wattron(win, COLOR_PAIR(7));
                mvwprintw(win, p.first, p.second, "o");
                wattroff(win, COLOR_PAIR(7));
            }
        }
    
}


void Snake::move(Map& map) {
    int y = body.front().first;
    int x = body.front().second;
    if (dir == UP) {
        body.push_front(make_pair(y - 1, x));
    } else if (dir == DOWN) {
        body.push_front(make_pair(y + 1, x));
    } else if (dir == LEFT) {
        body.push_front(make_pair(y, x - 1));
    } else if (dir == RIGHT) {
        body.push_front(make_pair(y, x + 1));
    }
    auto a = body.back();
    body.pop_back();
    map.setObject(a.first, a.second, 0);
}

void Snake::grow() {
    int y = body.front().first;
    int x = body.front().second;
    body.push_back(make_pair(y, x));
}

void Snake::degrow(Map& map) {
    auto a = body.back();
    body.pop_back();
    if(body.size() < 3) {
        isDead = true;
    }
    map.setObject(a.first, a.second, 0);
}

void Snake::interact(int y, int x, int point, Map& map, Score& score) {
    if (body.front().first == y && body.front().second == x) {
        switch (point) {
                case 0:
                    break;
                case 1:
                    isDead = true;
                    break;
                case 2:
                    isDead = true;
                    break;
                case 3: // Gate
                    gate(y, x, map);
                    score.setCurrentGate(score.getCurrentGate() + 1);
                    break;
                case 4:
                    grow();
                    map.setObject(y, x, 0);
                    map.makeItem();
                    score.setCurrentGrowth(score.getCurrentGrowth() + 1);
                    break;
                case 5:
                    degrow(map);
                    map.setObject(y, x, 0);
                    map.makePoison();
                    score.setCurrentPoison(score.getCurrentPoison() + 1);
                    break;
                case 6:
                    isDead = true;
                    break;

            }
    }
}
    // not head, only body set '6' on mapdata
void Snake::makeSnake(Map& map) {
    for (auto p : body) {
        if(p != body.front()) map.setObject(p.first, p.second, 6);
    }
}
    


void Snake::gate(int y, int x, Map map) { 
    // find out gate, x,y is enter gate
    int another_y, another_x;
    for (int i = 0; i < map.getHeight(); i++) {
        for (int j = 0; j < map.getWidth(); j++) {
            if (map.getObject(i, j) == 3 && (i != y || j != x)) {
                another_y = i;
                another_x = j;
            }
        }
    }
    body.pop_front();
    // if out gate is on edge, snake's dir is wall's opposite dir
    if (another_y == 0) {
        dir = DOWN;
    } else if (another_y == map.getHeight() - 1) {
        dir = UP;
    } else if (another_x == 0) {
        dir = RIGHT;
    } else if (another_x == map.getWidth() - 1) {
        dir = LEFT;
    } else { // if out gate is not on edge, snake's dir follows 
             //original dir, clockwise dir, counter-clockwise dir, opposite dir
        if (dir == UP) {
            if (map.getObject(another_y-1, another_x) != 1) {
                dir = UP;
            } else if (map.getObject(another_y, another_x+1) != 1) {
                dir = RIGHT;
            } else if (map.getObject(another_y, another_x-1) != 1) {
                dir = LEFT;
            } else {
                dir = DOWN;
            }
        } else if (dir == DOWN) {
            if (map.getObject(another_y+1, another_x) != 1) {
                dir = DOWN;
            } else if (map.getObject(another_y, another_x+1) != 1) {
                dir = RIGHT;
            } else if (map.getObject(another_y, another_x-1) != 1) {
                dir = LEFT;
            } else {
                dir = UP;
            }
        } else if (dir == LEFT) {
            if (map.getObject(another_y, another_x-1) != 1) {
                dir = LEFT;
            } else if (map.getObject(another_y-1, another_x) != 1) {
                dir = UP;
            } else if (map.getObject(another_y+1, another_x) != 1) {
                dir = DOWN;
            } else {
                dir = RIGHT;
            }
        } else if (dir == RIGHT) {
            if (map.getObject(another_y, another_x+1) != 1) {
                dir = RIGHT;
            } else if (map.getObject(another_y-1, another_x) != 1) {
                dir = UP;
            } else if (map.getObject(another_y+1, another_x) != 1) {
                dir = DOWN;
            } else {
                dir = LEFT;
            }
        } 
    }

    // move snake to out gate
    if(dir == UP) {
        body.push_front(make_pair(another_y-1, another_x));
    } else if (dir == DOWN) {
        body.push_front(make_pair(another_y+1, another_x));
    } else if (dir == LEFT) {
        body.push_front(make_pair(another_y, another_x-1));
    } else if (dir == RIGHT) {
        body.push_front(make_pair(another_y, another_x+1));
    }
}

bool Snake::getIsDead() {
    return isDead;
}

int Snake::getsize() {
    return body.size();
}

pair<int, int> Snake::getHead() {
    return body.front();
}

Direction Snake::getDir(){
    return dir;
}
