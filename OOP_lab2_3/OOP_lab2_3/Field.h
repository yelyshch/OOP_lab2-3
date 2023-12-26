#pragma once
#include "Character.h"
#include "Cell.h"
#include <vector>

struct Position {
    int x;
    int y;

    Position(int valueX, int valueY);

    Position();
};

class Field {
private:
    int width;
    int height;
    bool isCellFreeAroundHero(int heroX, int heroY) const;
    //friend void PrintField(Field*);

public:
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<int>> cell;
    Hero* hero;
    Monster* monster;
    Field(int m, int n);
    Field(const Field& other);
    Field& operator=(const Field& other);
    bool isWithinBounds(int x, int y) const;
    void placeHero();
    void placeMonsters(int monsterCount);
    void placeObstacles(int obstacleCount);
    bool freeCell(int x, int y) const;
    // Copy Constructor
    //Field(const Field& other);
    ~Field();

    void moveUnit(Character& unit, Position newPosition);

    void eraseContent(int x, int y);

    void moveHero(int x, int y);
};
