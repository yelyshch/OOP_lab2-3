#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include "Position.h"


class Manager;
class Monster;

const int maxHP = 10;

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
    void setHealth(int value);
    void setDamage(int value);
    void setProtection(int value);
    void setSpeed(int value);
    void setDistance(int value);


    void increaseHealth(int amount);
    void increaseDamage(int amount);
    void increaseProtection(int amount);
    void reduceHealth(int amount);

    void diceResults();
};
