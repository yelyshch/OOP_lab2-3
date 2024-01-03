#include "SlowMoveMonster.h"
#include "Monster.h"
#include "Position.h"
#include "Field.h"
#include "NormalMoveMonster.h"
#include <cmath>

void SlowMoveMonster::nextState() {
    monster->setMonsterState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    bool moveIsMade = false;
    //ϳ����� - ���������� �� ��������
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    while (!moveIsMade) {
        Position value;

        //������ �� X
        value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);

        if (gameField->freeCell(value)) {
                monster.setPosition(value);
                moveIsMade = true;
        }
        else if (deltaY != 0) {
            // ���� ��� �� X ����������, ��� ����� �� Y
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
            if (gameField->freeCell(value)) {
                monster.setPosition(value);
                moveIsMade = true;
            }
        }
    }
}
