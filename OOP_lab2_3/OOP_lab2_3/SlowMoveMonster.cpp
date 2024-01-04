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
        nextState(); 
    }
    else if (counter < 2 && counter > 0) { moveTowardsHero(monster, hero, gameField); }
}

void SlowMoveMonster::nextState() {
    monster->setMonsterState(new NormalMoveMonster());
}

void SlowMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField)
{
    bool moveIsMade = false;
    //Пізніше - передавати ці значення
    int deltaX = monster.getPosition().x - hero.getPosition().x;
    int deltaY = monster.getPosition().y - hero.getPosition().y;

    while (!moveIsMade) {
        Position value;

        if (deltaX != 0) {
            //Ходимо по X
            value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);
        }
        else if (deltaY != 0) {
            // Якщо рух по X неможливий, але можна по Y
            value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
            if (gameField->freeCell(value)) {
                gameField->eraseContent(monster.getPosition()); // erase the cell
                monster.setPosition(value);

                gameField->moveHero(value);
                moveIsMade = true;
            }
        }
        if (gameField->freeCell(value)) {
            gameField->eraseContent(monster.getPosition()); // erase the cell
            monster.setPosition(value);

            gameField->moveHero(value);
            moveIsMade = true;
        }

    }
}
