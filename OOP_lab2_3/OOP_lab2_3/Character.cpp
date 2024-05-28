#include "Character.h"
#include "Manager.h"
#include "cstdlib"
#include "Field.h"
#include "Position.h"
#include <array>

Character::Character() {
    health = 1;
    protection = 1;
    damage = 1;
    distance = 1;
}

int Character::getDamage() const { return damage; }
int Character::getSpeed() const { return speed; }
int Character::getHealth() const { return health; }
Position Character::getPosition() const { return char_position; }
int Character::getProtection() const { return protection; }
int Character::getDistance() const { return distance; }


void Character::setPosition(Position value) {
    char_position.x = value.x;
    char_position.y = value.y;
}

void Character::setHealth(int value) { health = value; }
void Character::setDamage(int value) { damage = value; }
void Character::setProtection(int value) { protection = value; }
void Character::setSpeed(int value) { speed = value; }
void Character::setDistance(int value) { distance = value; }


void Character::increaseHealth(int amount) { setHealth(getHealth() + amount); }
void Character::reduceHealth(int amount) {
    health -= amount;
    health = (health < 0) ? 0 : health;
}
void Character::increaseDamage(int amount) { setDamage(getDamage() + amount); }
void Character::increaseProtection(int amount) { setProtection(getProtection() + amount); }

void Character::diceResults() {}