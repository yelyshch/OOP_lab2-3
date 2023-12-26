#include "Field.h"
#include <cstdlib> // for rand()
#include <vector>

Position::Position(int valueX, int valueY)
{
    x = valueX;
    y = valueY;
}
Position::Position() {}

Field::Field(int n, int m) : width(n), height(m), cells(height, std::vector<Cell>(width, Cell()))
{
    hero = new Hero();
    monster = new Monster;
}

// Copy constructor
Field::Field(const Field& other)
    : width(other.width), height(other.height), cells(other.cells)
{
    // Create new instances for the hero and monster, copying their states
    hero = new Hero(*other.hero);
    monster = new Monster(*other.monster);
}

// Copy assignment operator
Field& Field::operator=(const Field& other)
{
    if (this != &other) {
        // Copy the basic properties
        width = other.width;
        height = other.height;
        cells = other.cells;

        delete hero;
        delete monster;

        // Create new
        hero = new Hero(*other.hero);
        monster = new Monster(*other.monster);
    }
    return *this;
}

//Переробити для юнітів, а не тільки героя
bool Field::isCellFreeAroundHero(int heroX, int heroY) const {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int x = heroX + dx;
            int y = heroY + dy;

            if (isWithinBounds(x, y) && (cells[y][x].hasObstacle() || cells[y][x].hasUnitPresent()))
                return false;
        }
    }
    return true;
}

bool Field::freeCell(int x, int y) const {
    return isWithinBounds(x, y) && !cells[y][x].hasObstacle() && !cells[y][x].hasUnitPresent();
}

void Field::placeHero() {
    Position value(width / 2, 0);
    hero->setPosition(value);
    moveUnit(*hero, value);
    cells[value.y][value.x].setUnitPresent(true);
}

void Field::placeObstacles(int obstacleCount) {
    for (int i = 0; i < obstacleCount; ++i) {
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (!isCellFreeAroundHero(x, y));

        cells[y][x].setObstacle(true);
    }
}

void Field::placeMonsters(int monsterCount) {
    for (int i = 0; i < monsterCount; ++i) {
        Position position;
        do {
            position.x = rand() % width;
            position.y = rand() % height;
        } while (!isCellFreeAroundHero(position.x, position.y));

        //Після вирішення проблем з конструктором Character повернутися
        monster->setX(position.x);
        monster->setY(position.y);
        cells[position.y][position.x].setUnitPresent(true);
    }
}

bool Field::isWithinBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Field::eraseContent(int x, int y) {
    if (isWithinBounds(x, y)) {
        cells[y][x].setUnitPresent(false);
        cells[y][x].setObstacle(false);
    }
}

void Field::moveHero(int x, int y) {
    if (isWithinBounds(x, y)) {
        cells[y][x].setUnitPresent(true);
    }
}

void Field::moveUnit(Character& unit, Position newPosition) {
    cells[unit.getPosition().x][unit.getPosition().y].setUnitPresent(false);
    cells[newPosition.y][newPosition.x].setUnitPresent(true);
}

Field::~Field() {
    delete hero;
    delete monster;
}
