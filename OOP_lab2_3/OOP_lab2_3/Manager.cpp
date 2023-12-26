#include "Manager.h"
#include "Character.h"
#include <iostream>

using namespace std;

Manager::Manager() : CurrentLevel(1), gameField(nullptr), PersoneName("") {}

void Manager::createField(int fieldWidth, int fieldHeight, int obstacles, int monster) {
    gameField = new Field(fieldWidth, fieldHeight);
    generationObjects(obstacles);
}

void Manager::generationObjects(int obst) const {
    gameField->placeHero();
    gameField->placeMonsters(1);
    gameField->placeObstacles(obst);
}

int Manager::getCurrentLevel() const {
    return CurrentLevel;
}

Manager::~Manager() {
    delete gameField;
}