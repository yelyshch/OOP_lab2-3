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

    // ���� ������ �� �� ������� �� ���� X � Y
    if (!movedAlongX && !movedAlongY) {
        // ��������, �� ������� �������� �� �� X
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
        // ���� ��� �� �� X �� ��������, �� ���������� �� �� Y
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
    // ���� ��� �� ��� ���������
    if (!moveIsMade) {
        if (movedAlongX) {
            // ���������� ���� ������/����� �� �����
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
            // ���������� ��� ��� �� �����
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

                // ���� ��������, ���� ����� ������� ����
                if (leftFree && rightFree) {
                    value = (rand() % 2 == 0) ? leftCell : rightCell;
                }
                // ���� ����� ��� �������
                else if (leftFree) {
                    value = leftCell;
                }
                // ���� ����� ����� �������
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

                // ���� ��������, ���� ����� ������� ����
                if (upFree && downFree) {
                    value = (rand() % 2 == 0) ? upCell : downCell;
                }
                // ���� ����� ������ �������
                else if (upFree) {
                    value = upCell;
                }
                // ���� ����� ����� �������
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