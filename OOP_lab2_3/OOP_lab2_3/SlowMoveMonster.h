#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class SlowMoveMonster: public State {
public:
    void stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField);
    void nextState();
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
};