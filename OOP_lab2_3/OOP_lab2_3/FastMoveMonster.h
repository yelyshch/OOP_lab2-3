#pragma once

#include "Monster.h"
#include "Hero.h"
#include "State.h"

class FastMoveMonster : public State {
public:
    void previousState() override;
    void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
    int getDirection(const Position& from, const Position& to);
};