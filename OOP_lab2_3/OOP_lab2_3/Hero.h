#pragma once
#include <stdlib.h>
#include "Character.h"
#include "Monster.h"

class Hero : public Character {
public:
    Hero();

    void increaseDistance(int amount);
    virtual void move(Position newCoordinates, Field* gameField);
    virtual void attack(Monster& target, Field* gameField);
    void restoreHealth();

    void diceResults();
    virtual ~Hero();
public:
    const int maxHP = 10; // Assuming maxHP is a constant for Hero
};

enum class HeroType {
    Archer,
    Swordsman
};