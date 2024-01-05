#include "NormalMoveMonster.h"
#include "FastMoveMonster.h"
#include "SlowMoveMonster.h"
#include "Field.h"
#include "Position.h"
#include <cmath>

void NormalMoveMonster::stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField) {
    if (counter < 3)
    {
        SlowMoveMonster nextstate;
        nextstate.stateDetermination(counter, monster, hero, gameField);
        this->monster = &monster;
        previousState();
    }
    else if (counter > 6)
    {
        FastMoveMonster nextstate;
        nextstate.stateDetermination(counter, monster, hero, gameField);
        this->monster = &monster;
        nextState();
    }
    else { moveTowardsHero(monster, hero, gameField); }
}

void NormalMoveMonster::nextState() {
    monster->setMonsterState(new FastMoveMonster());
}

void NormalMoveMonster::previousState() {
    monster->setMonsterState(new SlowMoveMonster());
}

void NormalMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    bool moveIsMade = false;
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    while (!moveIsMade) {
        Position value;

        // ƒ≥агональний рух, пр≥оритетний

        if (std::abs(deltaX) >= 2 && std::abs(deltaY) >= 2) {
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0),
                monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);

                gameField->moveHero(value);
                moveIsMade = true;
            }
        }
        else {
            //’одимо по X
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);

            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);
                gameField->moveHero(value);

                monster.setAttackCounter(monster.getAttackCounter() + 1);
                moveIsMade = true;
            }
            else if (deltaY != 0) {
                // якщо рух по X неможливий, але можна по Y
                value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
                if (gameField->freeCell(value)) {
                    gameField->eraseContent(monster.getPosition()); // erase the cell
                    monster.setPosition(value);
                    gameField->moveHero(value);

                    monster.setAttackCounter(monster.getAttackCounter() + 1);
                    moveIsMade = true;
                }
            }
        }
    }
}