#include "Archer.h"
#include "Hero.h"
#include "Field.h"

Archer::Archer() noexcept : Hero() {
    setProtection(1);
    setDamage(1);
    setDistance(3);
    setSpeed(3);
}

int Archer::move(Position newCoordinates, Field* gameField){
    if (gameField->freeCell(newCoordinates)) {
        int deltaX = std::abs(newCoordinates.x - getPosition().x);
        int deltaY = std::abs(newCoordinates.y - getPosition().y);

        int moveCost = 0;
        if (deltaX == 1 && deltaY == 1) {
            moveCost = 2; // move diagonally
        }
        else {
            moveCost = 1; // move straight or diagonally by more cells
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

void Archer::attack(Monster& target, Field* gameField) {
    int damage = std::abs(getDamage() - target.getProtection());
    int additionalSpeed = 0;

    // Probability of gaining additional speed
    if (rand() % 100 < 25) {
        additionalSpeed = 1;
    }

    int totalDamage = damage + additionalSpeed;

    // Apply damage to the monster
    target.setHealth(std::max(0, target.getHealth() - totalDamage));

    // Check if the monster is defeated
    if (target.getHealth() <= 0) {
        target.setHealth(0);
        gameField->eraseContent(target.getPosition()); // Erase the cell
    }
}

Archer::~Archer() {}