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
    setHealth(3);
    state = nullptr;
    attackCounter = 0;
}

Monster::Monster(State* st) : state(nullptr) {
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


void Monster::activityInGame(Monster& monster, Hero& hero, Field* gameField) {
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    Monster* monsterState = new Monster(new SlowMoveMonster());

    if (std::abs(deltaX) <= 1 && std::abs(deltaY) <= 1) { monster.calculateMonsterAttack(hero, monster); }
    else {
        if (state == SlowMoveMonster() && attackCounter = 3) {
            monster.nextState();
        }
        else if (state == NormalMoveMonster() && attackCounter = 6) {
            monster.nextState();
        }
        else if (state == FastMoveMonster() && attackCounter = 5) {
            monster.previousState();
        }
        else if (state == NormalMoveMonster() && attackCounter = 2) {
            monster.previousState();
        }

        if (state == SlowMoveMonster()) {
            SlowMoveMonster currentState;
            currentState.moveTowardsHero(monster, hero, gameField);
        }
        else if (state == NormalMoveMonster()) {
            NormalMoveMonster currentState;
            currentState.moveTowardsHero(monster, hero, gameField);
        }
        else {
            FastMoveMonster currentState;
            currentState.moveTowardsHero(monster, hero, gameField);
        }
    }
}


void Monster::calculateMonsterAttack(Hero& hero, Monster& monster) {
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