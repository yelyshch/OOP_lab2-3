#pragma once
#include "Field.h"
#include "Character.h"
#include "Hero.h"

class Manager {
private:
    std::string PersoneName;
    HeroType heroType; 
public:
    int CurrentLevel;
    //friend void TestLab1(Manager);
    Field* gameField;

    void createField(int fieldWidth, int fieldHeight, int obstacles, int monster, HeroType typeHero);

    void generationObjects(int obst) const;
    int getCurrentLevel() const;
    Manager();
    ~Manager();
};
