#include <stdlib.h>
#include "Hero.h"
#include "Field.h"
#include "Monster.h"

Hero::Hero() noexcept : Character() { setHealth(10); }
void Hero::increaseDistance(int amount) { setDistance(getDistance() + amount); }
void Hero::restoreHealth() { setHealth(maxHP); }
void Hero::diceResults() {
    setSpeed(getSpeed() + (rand() % 6 + 1));
    setDamage(getDamage() + (rand() % 6 + 1));
    setProtection(getProtection() + (rand() % 6 + 1));
}
Hero::~Hero() {}