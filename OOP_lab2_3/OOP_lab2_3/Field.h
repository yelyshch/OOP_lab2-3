#pragma once
#include "Character.h"
#include "Cell.h"
#include <vector>
#include "Hero.h"

class Field {
private:
    int width;
    int height;
    bool isCellFreeAroundHero(Position unutPosition) const;
    bool isCellFreeForObstacle(Position unutPosition) const;

    //friend void PrintField(Field*);

public:
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<int>> cell;
    Hero* hero;
    Monster* monster;
    Field(int n, int m, HeroType heroType);
    bool isWithinBounds(Position value) const;
    void placeHero();
    void placeMonsters(int monsterCount);
    void placeObstacles(int obstacleCount);
    bool freeCell(Position newXY) const;
    ~Field();

    void moveUnit(Character& unit, Position newPosition);

    void eraseContent(Position cell);

    void moveHero(Position moving);
};
