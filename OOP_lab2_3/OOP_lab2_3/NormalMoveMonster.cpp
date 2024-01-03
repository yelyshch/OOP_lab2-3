#include "NormalMoveMonster.h"
#include "SlowMoveMonster.h"
#include "Field.h"
#include "Position.h"

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
        if ((deltaX >= 2 || deltaX <= -2) && (deltaY >= 2 || deltaY <= -2)) {
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0),
                                 monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
        }
        else {
            //������ �� X
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);

            if (gameField->freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // ���� ��� �� X ����������, ��� ����� �� Y
                value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
                if (gameField->freeCell(value)) {
                    monster.setPosition(value);
                }
            }
        }

        // �������� ���������� ���� �������
        if (gameField->freeCell(value)) {
            monster.setPosition(value);
            moveIsMade = true;
        }
    }
}