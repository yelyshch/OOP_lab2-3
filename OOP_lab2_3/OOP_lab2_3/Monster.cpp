#include <iostream>
#include "Position.h"
#include "Hero.h"
#include "Monster.h"
#include "State.h"
#include "NormalMoveMonster.h"
#include "FastMoveMonster.h"
#include "SlowMoveMonster.h"
#include <cmath>


Monster::Monster() noexcept : Character() {
    setProtection(1);
    setDamage(1);
    setHealth(7);
    state = new SlowMoveMonster();
    attackCounter = 0;
}

Monster::Monster(State* st){
    setMonsterState(st);
}

Monster::~Monster() {
    if (state != nullptr) {
        delete state;
    }
}

State* Monster::getMonsterState() { return state; }

void Monster::setMonsterState(State* newState) {
    if (state != nullptr) { delete state; }
    state = newState;
    state->setStateForMonster(this);
}

void Monster::nextState() {
    state->nextState();
}

void Monster::previousState() {
    state->previousState();
}

int Monster::getAttackCounter() { return attackCounter; }
void Monster::setAttackCounter(int value) { attackCounter = value; }

void Monster::activityInGame(Monster& monster, Hero& hero, Field* gameField) {
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    if (std::abs(deltaX) <= 1 && std::abs(deltaY) <= 1) { monster.calculateMonsterAttack(hero, monster); }
    else { state->stateDetermination(attackCounter, monster, hero, gameField); }
}


void Monster::calculateMonsterAttack(Hero& hero, Monster& monster) {
    int monsterDistance = std::max(std::abs(hero.getPosition().x - monster.getPosition().x), std::abs(hero.getPosition().y - monster.getPosition().y));

    if (monster.getHealth() > 0) {
        int totalAttack = (monsterDistance <= hero.getDistance()) ? monster.getDamage() : 0;
        int damage = (totalAttack > hero.getProtection()) ? (totalAttack - hero.getProtection()) : 0;

        if (damage > 0) {
            hero.reduceHealth(damage);
        }
        else {
            hero.setProtection(hero.getProtection() - std::ceil(getDamage()/3));
        }
    }
}

void Monster::diceResults() {
    setDamage(getDamage() + (rand() % 6 + 1));
    setProtection(getProtection() + (rand() % 6 + 1));
}