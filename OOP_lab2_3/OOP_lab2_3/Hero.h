#pragma once
#include <stdlib.h>
#include "Character.h"
#include "Monster.h"

class Hero : public Character {
public:
    Hero() noexcept;

    void increaseDistance(int amount);
    virtual int move(Position newCoordinates, Field* gameField) = 0;
    virtual void attack(Monster& target, Field* gameField) = 0;
    void restoreHealth();
    virtual ~Hero();
public:
    const int maxHP = 10; // Assuming maxHP is a constant for Hero
};

enum class HeroType {
    Archer,
    Swordsman
};
