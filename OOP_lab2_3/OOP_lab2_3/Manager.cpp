#include "Manager.h"
#include "Character.h"
#include "Hero.h"
#include <iostream>

using namespace std;

Manager::Manager() : CurrentLevel(1), gameField(nullptr), PersoneName("") {}

HeroType Manager::getHeroType(bool choice) {
    if (choice == 0) {
        return HeroType::Archer;
    }
    else if (choice == 1) {
        return HeroType::Swordsman;
    }
    else {
        return HeroType::Archer;
    }
}

void Manager::createField(int fieldWidth, int fieldHeight, int obstacles, int monster, bool choice) {
    heroType = getHeroType(choice);
    gameField = new Field(fieldWidth, fieldHeight, heroType);
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