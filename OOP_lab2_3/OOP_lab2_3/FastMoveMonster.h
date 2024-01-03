#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class FastMoveMonster : public State {
public:
    void previousState();
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);

};