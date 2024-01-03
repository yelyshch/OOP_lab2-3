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
    HeroType getHeroType(bool choice);

    void createField(int fieldWidth, int fieldHeight, int obstacles, int monster, bool choice);

    void generationObjects(int obst) const;
    int getCurrentLevel() const;
    Manager();
    ~Manager();
};
