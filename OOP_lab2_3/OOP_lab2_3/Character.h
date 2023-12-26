#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include "Position.h"

class Manager;
class Monster;

const int maxHP = 10;
const int startValue = 1;

class Field;

class Character {
private:
    Position char_position;
    int health;
    int protection;
    int damage;
    int speed;
    int distance;

public:
    Character();
    int getDamage() const;
    int getSpeed() const;
    int getHealth() const;
    Position getPosition() const;
    int getProtection() const;
    int getDistance() const;

    void setPosition(Position value);
    //void setX(int x);
    //void setY(int y);
    void setHealth(int value);
    void setDamage(int value);
    void setProtection(int value);
    void setSpeed(int value);
    void setDistance(int value);


    void increaseHealth(int amount);
    void increaseDamage(int amount);
    void increaseProtection(int amount);
    void reduceHealth(int amount);
};

class Hero : public Character {
public:
    using Character::Character;
    using Character::getHealth;
    using Character::reduceHealth;
    Hero() noexcept;

    void increaseDistance(int amount);
    void restoreHealth();
    int move(Position newCoordinates, Field* gameField);
    void attack(Monster& target, Field* gameField);

    void diceResults();
};

class Monster : public Character {
private:
    bool active{};

public:

    using MonsterContainer = std::array<Monster, 5>;
    using Character::Character;
    Monster() noexcept;

    using Character::getHealth;
    using Character::getDamage;
    using Character::setHealth;
    using Character::reduceHealth;

    void calculateMonsterAttack(Hero& hero, MonsterContainer& monsters);
};
