#include "SlowMoveMonster.h"
#include "Monster.h"
#include "Position.h"
#include "Field.h"

void SlowMoveMonster::nextState() {
    //monster->setMonsterState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    bool moveX = rand() % 2 == 0; // ¬изначаЇмо чи будемо рухатис€ по X чи Y

    if (moveX) { 
        if (deltaX > 0) {
            // Ћог≥ка дл€ руху вл≥во
            Position value;
            value.setCoordinates(monster.getPosition().x - 1, monster.getPosition().y);
            if (gameField->freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // якщо рух по X неможливий, але можна по Y
                Position yValue;
                yValue.setCoordinates(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (gameField->freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
        else if (deltaX < 0) {
            // Ћог≥ка дл€ руху вправо
            Position value;
            value.setCoordinates(monster.getPosition().x + 1, monster.getPosition().y);
            if (gameField->freeCell(value)) {
                monster.setPosition(value);
            }
            else if (deltaY != 0) {
                // якщо рух по X неможливий, але можна по Y
                Position yValue;
                yValue.setCoordinates(monster.getPosition().x, monster.getPosition().y + (deltaY > 0 ? -1 : 1));
                if (gameField->freeCell(yValue)) {
                    monster.setPosition(yValue);
                }
            }
        }
    }
    else {
        if (deltaY > 0) {
            // Ћог≥ка дл€ руху вгору
            Position value;
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y - 1);
            if (gameField->freeCell(value)) {
                monster.setPosition(value);
            }
        }
        else if (deltaY < 0) {
            // Ћог≥ка дл€ руху вниз
            Position value;
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y + 1);
            if (gameField->freeCell(value)) {
                monster.setPosition(value);
            }
        }
    }
}
