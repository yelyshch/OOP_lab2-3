#include "Field.h"
#include "Position.h"
#include <cstdlib> // for rand()
#include <vector>

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
bool Field::isCellFreeAroundHero(Position unutPosition) const {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            Position value;
            value.x = unutPosition.x + dx;
            value.y = unutPosition.y + dy;

            if (isWithinBounds(value) && (cells[value.y][value.x].hasObstacle() || cells[value.y][value.x].hasUnitPresent()))
                return false;
        }
    }
    return true;
}

bool Field::freeCell(Position newXY) const {
    return isWithinBounds(newXY) && !cells[newXY.y][newXY.x].hasObstacle() && !cells[newXY.y][newXY.x].hasUnitPresent();
}

void Field::placeHero() {
    Position value; 
    value.setCoordinates(width / 2, 0);
    hero->setPosition(value);
    moveUnit(*hero, value);
    cells[value.y][value.x].setUnitPresent(true);
}

void Field::placeObstacles(int obstacleCount) {
    for (int i = 0; i < obstacleCount; ++i) {
        Position value;
        do {
            value.x = rand() % width;
            value.y = rand() % height;
        } while (!isCellFreeAroundHero(value));
        cells[value.y][value.x].setObstacle(true);
    }
}

void Field::placeMonsters(int monsterCount) {
    for (int i = 0; i < monsterCount; ++i) {
        Position position;
        do {
            position.x = rand() % width;
            position.y = rand() % height;
        } while (!isCellFreeAroundHero(position));

        monster->setPosition(position);
        cells[position.y][position.x].setUnitPresent(true);
    }
}

bool Field::isWithinBounds(Position value) const {
    return value.x >= 0 && value.x < width && value.y >= 0 && value.y < height;
}

void Field::eraseContent(Position cell) {
    if (isWithinBounds(cell)) {
        cells[cell.y][cell.x].setUnitPresent(false);
        cells[cell.y][cell.x].setObstacle(false);
    }
}

void Field::moveHero(Position moving) {
    if (isWithinBounds(moving)) {
        cells[moving.y][moving.x].setUnitPresent(true);
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
