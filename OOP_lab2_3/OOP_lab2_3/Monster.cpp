#include "Hero.h"
#include "Monster.h"
#include "State.h"
#include <cmath>

Monster::Monster() noexcept : Character() {
    setProtection(1);
    setDamage(1);
    setHealth(3);
    state = nullptr;
}

Monster::Monster(State* st) : Character() {
    setMonsterState(st);
}

State* Monster::getMonsterState() { return state; }

void Monster::setMonsterState(State* newState) {
    if (state != nullptr) delete state;
    state = newState;
    state->setStateForMonster(this);
}

void Monster::nextState() {
    state->nextState();
}

void Monster::previousState() {
    state->previousState();
}

void Monster::moveTowardsHero(Hero& hero) {

}

void Monster::calculateMonsterAttack(Hero& hero, MonsterContainer& monsters) {
    for (Monster& monster : monsters) {
        int monsterDistance = std::max(std::abs(hero.getPosition().x - monster.getPosition().x), std::abs(hero.getPosition().y - monster.getPosition().y));

        int totalAttack;
        if (monster.getHealth() > 0) {
            if (monsterDistance <= hero.getDistance()) {
                totalAttack = monster.getDamage();
            }
            else {
                totalAttack = 0;
            }
        }
        else {
            return;
        }

        int heroDefense = hero.getProtection();
        int damage;

        if (totalAttack > heroDefense) {
            damage = totalAttack - heroDefense;
        }
        else {
            damage = 0;
        }

        hero.reduceHealth(damage);
    }
}