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

        // ĳ���������� ���, �����������

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
            // ���� ������ �� �� ������� �� ���� X � Y
            if (!movedAlongX && !movedAlongY) {
                // ��������, �� ������� �������� �� �� X
                if (deltaX != 0) {
                    value.setCoordinates(monster.getPosition().x + ((deltaX > 0) ? -1 : 1), monster.getPosition().y);
                    if (gameField->freeCell(value)) {
                        gameField->eraseContent(monster.getPosition());
                        monster.setPosition(value);
                        gameField->moveHero(value); // ���� �� moveHero

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
                        gameField->moveHero(value); // ���� �� moveHero

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
                        }
                    }
                    movedAlongX = false;
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
                        }
                    }
                    movedAlongY = false;
                }
                else {
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
                        }
                    }
                }
            }
        }
    }
}