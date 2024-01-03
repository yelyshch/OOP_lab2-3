#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class NormalMoveMonster;

class NormalMoveMonster : public State {
public:
    void nextState();
    void previousState();
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
};
