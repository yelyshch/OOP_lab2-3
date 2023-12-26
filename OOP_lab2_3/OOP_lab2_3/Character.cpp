#include "Character.h"
#include "Manager.h"
#include "cstdlib"
#include "Field.h"
#include "Position.h"
#include <array>

//Character

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
//Clean up when fix the monster
//void Character::setX(int x) { char_position.x = x; }
//void Character::setY(int y) { char_position.y = y; }

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

//Hero

Hero::Hero() noexcept : Character() {
    setDistance(1);
    setSpeed(1);
    setHealth(10);
    setProtection(1);
    setDamage(1);
}

void Hero::increaseDistance(int amount) { setDistance(getDistance() + amount); }


void Hero::diceResults() {
    setSpeed(getSpeed() + (rand() % 6 + 1));
    setDamage(getDamage() + (rand() % 6 + 1));
    setProtection(getProtection() + (rand() % 6 + 1));
}

int Hero::move(Position newCoordinates, Field* gameField) {
    if (gameField->freeCell(newCoordinates)) {
        int deltaX = std::abs(newCoordinates.x - getPosition().x);
        int deltaY = std::abs(newCoordinates.y - getPosition().y);

        int moveCost = 0;
        if (deltaX == deltaY) { // diagonal
            if (deltaX == 1 && deltaY == 1) {
                moveCost = 2; // move 1 cell - 2 points
            }
            else {
                moveCost = 2 + (deltaX - 1); // move by more cells
            }
        }
        else { // straight movement
            moveCost = std::max(deltaX, deltaY);
        }

        int curSpeed = getSpeed();
        if (curSpeed >= moveCost) {
            gameField->eraseContent(getPosition()); // erased the cell
            
            setPosition(newCoordinates);
            gameField->moveHero(newCoordinates); // updated the field

            curSpeed -= moveCost;
        }
        return moveCost;
    }
    return 1;
}

void Hero::attack(Monster& target, Field* gameField) {
    int target_x = target.getPosition().x;
    int target_y = target.getPosition().y;

    int deltaX = std::abs(target_x - getPosition().x);
    int deltaY = std::abs(target_y - getPosition().y);

    int moveCost = 0;
    if (deltaX == deltaY) { // diagonal
        if (deltaX == 1 && deltaY == 1) {
            moveCost = 3; // move 1 cell - 3 points
        }
        else {
            moveCost = 3 + (deltaX - 1); // move by more cells
        }
    }
    else { // straight movement
        if (!deltaX || !deltaY) {
            moveCost = std::max(deltaX, deltaY) + 1;
        }
    }

    if (moveCost <= getDistance()) {
        int damageNeeded = target.getProtection();

        // check if the hero has enough damage points to attack
        if (getDamage() > damageNeeded) {
            int damageDealt = getDamage() - damageNeeded;
            target.setHealth(target.getHealth() - damageDealt);

            if (target.getHealth() <= 0) {
                target.setHealth(0);
                gameField->eraseContent(target.getPosition()); // erased the cell
            }
        }
    }
}


void Hero::restoreHealth() { setHealth(maxHP); }


//Monster

Monster::Monster() noexcept {
    Manager main;
    setSpeed(6);
    setProtection(1);
    setDamage(7);
    setHealth(12);
}

using MonsterContainer = std::array<Monster, 1>;

void Monster::calculateMonsterAttack(Hero& hero, MonsterContainer& monsters) {
    for (auto& monster : monsters) {
        int monsterDistance = std::max(std::abs(hero.getPosition().x - monster.getPosition().x), std::abs(hero.getPosition().y - monster.getPosition().y));

        int totalAttack;
        if (monster.getHealth()>0) {
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