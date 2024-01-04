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
        previousState();
    }
    else if (counter > 6)
    {
        FastMoveMonster nextstate;
        nextstate.stateDetermination(counter, monster, hero, gameField);
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

        // Діагональний рух, пріоритетний
        
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
            //Ходимо по X
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);

            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);

                gameField->moveHero(value);
                moveIsMade = true;
            }
            else if (deltaY != 0) {
                // Якщо рух по X неможливий, але можна по Y
                value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
                if (gameField->freeCell(value)) {
                    monster.setPosition(value);
                }
            }
        }

        // Перевірка доступності нової позиції
    }
}