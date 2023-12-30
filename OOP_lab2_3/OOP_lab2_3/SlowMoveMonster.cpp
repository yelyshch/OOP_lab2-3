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

    bool moveX = rand() % 2 == 0; // ¬изначаЇмо чи будемо рухатис€ по X чи Y

    if (moveX) {
        if (deltaX > 0) {
            // Ћог≥ка дл€ руху вл≥во
            Position value(monster.getPosition().x - 1, monster.getPosition().y);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // якщо рух по X неможливий, але можна по Y
                Position yValue(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
        else if (deltaX < 0) {
            // Ћог≥ка дл€ руху вправо
            Position value(monster.getPosition().x + 1, monster.getPosition().y);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // якщо рух по X неможливий, але можна по Y
                Position yValue(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
    }
    else {
        if (deltaY > 0) {
            // Ћог≥ка дл€ руху вгору
            Position value(monster.getPosition().x, monster.getPosition().y - 1);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
        }
        else if (deltaY < 0) {
            // Ћог≥ка дл€ руху вниз
            Position value(monster.getPosition().x, monster.getPosition().y + 1);
            if (freeCell(value)) {
                monster.setPosition(value);
            }
        }
    }
}
