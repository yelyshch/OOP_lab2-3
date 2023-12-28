#pragma once
#include "Character.h"
#include "Hero.h"
#include <vector>

class Hero;

class Monster : public Character {
public:
    Monster() noexcept;

    using MonsterContainer = std::vector<Monster>;

    void calculateMonsterAttack(Hero& hero, MonsterContainer& monsters);
};