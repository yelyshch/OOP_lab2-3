#pragma once

#include "Monster.h"
#include "Hero.h"

class SlowMoveMonster {
public:
    void nextState() override;
    void moveTowardsHero(Monster& monster, Hero& hero);
};