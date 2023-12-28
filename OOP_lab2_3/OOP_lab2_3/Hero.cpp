#include <stdlib.h>
#include "Hero.h"
#include "Field.h"
#include "Monster.h"

Hero::Hero() noexcept : Character() {
    setHealth(10);
}

void Hero::increaseDistance(int amount) { setDistance(getDistance() + amount); }

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