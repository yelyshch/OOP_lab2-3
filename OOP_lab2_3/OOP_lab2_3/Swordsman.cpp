#include "Swordsman.h"
#include "Hero.h"
#include "Field.h"

Swordsman::Swordsman() noexcept : Hero() {
    setProtection(3);
    setDamage(3);
    setDistance(1);
    setSpeed(1);
}

int Swordsman::move(Position newCoordinates, Field* gameField) {
    if (gameField->freeCell(newCoordinates)) {
        int deltaX = std::abs(newCoordinates.x - getPosition().x);
        int deltaY = std::abs(newCoordinates.y - getPosition().y);

        int moveCost = 0;
        if (deltaX == 1 && deltaY == 1) {
            moveCost = 3; // move diagonally
        }
        else {
            moveCost = 2; // move straight or diagonally by more cells
        }

        int curSpeed = getSpeed();
        if (curSpeed >= moveCost) {
            gameField->eraseContent(getPosition()); // erase the cell

            setPosition(newCoordinates);
            gameField->moveHero(newCoordinates); // update the field

            curSpeed -= moveCost;
        }
        return moveCost;
    }
    return 1;
}

void Swordsman::attack(Monster& target, Field* gameField) {
    int damage = std::abs(2 * getDamage() - target.getProtection());
    int additionalDamage = 0;

    // Counter for the number of attacks made in the round
    static int attackCounter = 0;

    // Probability of additional damage based on the attack counter
    if (attackCounter == 0) {
        if (rand() % 100 < 10) {
            additionalDamage = 2;
        }
    }
    else if (attackCounter == 1) {
        if (rand() % 100 < 25) {
            additionalDamage = 2;
        }
    }
    else if (attackCounter == 2) {
        if (rand() % 100 < 50) {
            additionalDamage = 2;
        }
    }
    else if (attackCounter == 3) {
        if (rand() % 100 < 75) {
            additionalDamage = 2;
        }
    }
    else if (attackCounter == 4) {
        if (rand() % 100 < 90) {
            additionalDamage = 2;
        }
    }
    else {
        // Guaranteed additional damage on the 5th attack
        additionalDamage = 2;
    }

    int totalDamage = damage + additionalDamage;

    // Apply damage to the monster
    target.setHealth(std::max(0, target.getHealth() - totalDamage));

    // Check if the monster is defeated
    if (target.getHealth() <= 0) {
        target.setHealth(0);
        gameField->eraseContent(target.getPosition()); // Erase the cell
    }

    // Increment the attack counter
    attackCounter = (attackCounter + 1) % 5;
}

Swordsman::~Swordsman() {};