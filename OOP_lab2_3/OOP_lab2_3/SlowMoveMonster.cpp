#include "SlowMoveMonster.h"
#include "Monster.h"
#include "Position.h"
#include "Field.h"
#include "NormalMoveMonster.h"
#include <cmath>

void SlowMoveMonster::stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField) {
    if (counter > 10) {
        NormalMoveMonster nextstate;
        nextstate.stateDetermination(counter, monster, hero, gameField);
        this->monster = &monster;
        nextState();
    }
    else if (counter < 10 && counter >= 0) { moveTowardsHero(monster, hero, gameField); }
}

void SlowMoveMonster::nextState() {
    monster->setMonsterState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    bool moveIsMade = false;

    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    Position value;

    // якщо монстр ще не рухавс€ по ос€х X ≥ Y
    if (!movedAlongX && !movedAlongY) {
        // ѕерев≥рка, чи потр≥бно рухатис€ по ос≥ X
        if (deltaX != 0) {
            value.setCoordinates(monster.getPosition().x + ((deltaX > 0) ? -1 : 1), monster.getPosition().y);
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition());
                monster.setPosition(value);
                gameField->moveHero(value);

                monster.setAttackCounter(monster.getAttackCounter() + 1);
                moveIsMade = true;
            }
        }
        // якщо рух по ос≥ X не можливий, то перев≥р€Їмо по ос≥ Y
        else if (deltaY != 0) {
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 0) ? -1 : 1));
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition());
                monster.setPosition(value);
                gameField->moveHero(value);

                monster.setAttackCounter(monster.getAttackCounter() + 1);
                moveIsMade = true;
            }
        }
    }
    // якщо рух не був зд≥йснений
    if (!moveIsMade) {
        if (movedAlongX) {
            // ѕримусовий крок вперед/назад до геро€
            if (deltaY != 0) {
                value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 0) ? -1 : 1));
                if (gameField->freeCell(value)) {
                    gameField->eraseContent(monster.getPosition());
                    monster.setPosition(value);
                    gameField->moveHero(value);

                    monster.setAttackCounter(monster.getAttackCounter() + 1);
                    movedAlongX = false;
                    moveIsMade = true;
                }
            }
        }
        else if (movedAlongY) {
            // ѕримусовий х≥д уб≥к до геро€
            if (deltaX != 0) {
                value.setCoordinates(monster.getPosition().x + ((deltaX > 0) ? -1 : 1), monster.getPosition().y);
                if (gameField->freeCell(value)) {
                    gameField->eraseContent(monster.getPosition());
                    monster.setPosition(value);
                    gameField->moveHero(value);

                    monster.setAttackCounter(monster.getAttackCounter() + 1);
                    movedAlongY = false;
                    moveIsMade = true;
                }
            }
        }
        else if(!movedAlongX && !movedAlongY){
            if (deltaX == 0) {
                Position leftCell;
                leftCell.setCoordinates(monster.getPosition().x - 1, monster.getPosition().y);
                Position rightCell;
                rightCell.setCoordinates(monster.getPosition().x + 1, monster.getPosition().y);

                bool leftFree = gameField->freeCell(leftCell);
                bool rightFree = gameField->freeCell(rightCell);

                // ¬иб≥р напр€мку, €кщо обидв≥ кл≥тинки в≥льн≥
                if (leftFree && rightFree) {
                    value = (rand() % 2 == 0) ? leftCell : rightCell;
                }
                // якщо в≥льна л≥ва кл≥тинка
                else if (leftFree) {
                    value = leftCell;
                }
                // якщо в≥льна права кл≥тинка
                else if (rightFree) {
                    value = rightCell;
                }

                if (gameField->freeCell(value)) {
                    gameField->eraseContent(monster.getPosition());
                    monster.setPosition(value);
                    gameField->moveHero(value);

                    monster.setAttackCounter(monster.getAttackCounter() + 1);
                    movedAlongX = true;
                    moveIsMade = true;
                }
            }
            else if (deltaY == 0) {
                Position upCell;
                upCell.setCoordinates(monster.getPosition().x, monster.getPosition().y - 1);
                Position downCell;
                downCell.setCoordinates(monster.getPosition().x, monster.getPosition().y + 1);

                bool upFree = gameField->freeCell(upCell);
                bool downFree = gameField->freeCell(downCell);

                // ¬иб≥р напр€мку, €кщо обидв≥ кл≥тинки в≥льн≥
                if (upFree && downFree) {
                    value = (rand() % 2 == 0) ? upCell : downCell;
                }
                // якщо в≥льна верхн€ кл≥тинка
                else if (upFree) {
                    value = upCell;
                }
                // якщо в≥льна нижн€ кл≥тинка
                else if (downFree) {
                    value = downCell;
                }

                if (gameField->freeCell(value)) {
                    gameField->eraseContent(monster.getPosition());
                    monster.setPosition(value);
                    gameField->moveHero(value);

                    monster.setAttackCounter(monster.getAttackCounter() + 1);
                    movedAlongY = true;
                    moveIsMade = true;
                }
            }
        }
    }
}