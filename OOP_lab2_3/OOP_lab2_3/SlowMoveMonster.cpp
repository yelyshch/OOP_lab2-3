#include "SlowMoveMonster.h"
#include "Monster.h"
#include "Cell.h"
#include "Position.h"
#include "Hero.h"
#include "Field.h"
#include "State.h"

void SlowMoveMonster::nextState() {
    monster->setState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero)
{
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    bool moveX = rand() % 2 == 0; // ��������� �� ������ �������� �� X �� Y

    if (moveX) {
        if (deltaX > 0) {
            // ����� ��� ���� ����
            Position value(monster.getPosition().x - 1, monster.getPosition().y);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // ���� ��� �� X ����������, ��� ����� �� Y
                Position yValue(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
        else if (deltaX < 0) {
            // ����� ��� ���� ������
            Position value(monster.getPosition().x + 1, monster.getPosition().y);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // ���� ��� �� X ����������, ��� ����� �� Y
                Position yValue(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
    }
    else {
        if (deltaY > 0) {
            // ����� ��� ���� �����
            Position value(monster.getPosition().x, monster.getPosition().y - 1);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
        }
        else if (deltaY < 0) {
            // ����� ��� ���� ����
            Position value(monster.getPosition().x, monster.getPosition().y + 1);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
        }
    }
}
