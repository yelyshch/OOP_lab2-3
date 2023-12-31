#include "SlowMoveMonster.h"
#include "Monster.h"
#include "Position.h"
#include "Field.h"
#include "NormalMoveMonster.h"
#include <cmath>

void SlowMoveMonster::stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField) {
    if (counter > 2) {
        NormalMoveMonster nextstate;
        nextstate.stateDetermination(counter, monster, hero, gameField);
        this->monster = &monster;
        nextState();
    }
    else if (counter < 3 && counter >= 0) { moveTowardsHero(monster, hero, gameField); }
}

void SlowMoveMonster::nextState() {
    monster->setMonsterState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    bool moveIsMade = false;
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    while (!moveIsMade) {
        Position value;

        if (deltaX != 0) {
            //������ �� X
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);
                gameField->moveHero(value);

                monster.setAttackCounter(monster.getAttackCounter() + 1);
                moveIsMade = true;
            }
            else ++deltaX; // TODO: Remove
        }
        else if (deltaY != 0) {
            // ���� ��� �� X ����������, ��� ����� �� Y
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);
                gameField->moveHero(value);

                monster.setAttackCounter(monster.getAttackCounter() + 1);
                moveIsMade = true;
            }
            else ++deltaY; // TODO: Remove
        }

    }
}

