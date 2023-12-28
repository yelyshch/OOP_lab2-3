#pragma once
#include <stdlib.h>
#include "Character.h"
#include "Monster.h"

class Hero : public Character {
public:
    Hero() noexcept;

    void increaseDistance(int amount);
    virtual int move(Position newCoordinates, Field* gameField);
    void attack(Monster& target, Field* gameField);
    void restoreHealth();
public:
    const int maxHP = 10; // Assuming maxHP is a constant for Hero
};
