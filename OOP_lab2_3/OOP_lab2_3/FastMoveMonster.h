#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class FastMoveMonster : public State {
public:
    void stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField);
    void previousState();
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
};