#pragma once

#include "Character.h"
#include <vector>

class Hero;
class State;

class Monster : public Character {
public:
    int numberOfMoving;
    Monster() noexcept;
    Monster(State* st);
    State* getMonsterState();
    void setMonsterState(State* newState);
    void nextState();
    void previousState();

    void activityInGame(Monster& monster, Hero& hero, Field* gameField);

    //void moveTowardsHero(Hero& hero);

    using MonsterContainer = std::vector<Monster>;

    void calculateMonsterAttack(Hero& hero, Monster& monster);
private:
    State* state;
    int attackCounter;
};