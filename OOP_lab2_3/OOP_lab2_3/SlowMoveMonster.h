#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class SlowMoveMonster: public State {
public:
    void nextState() override;
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
};