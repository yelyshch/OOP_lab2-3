#include "FastMoveMonster.h"
#include "NormalMoveMonster.h"
#include "SlowMoveMonster.h"
#include "Field.h"
#include "Position.h"
#include <cmath>

void FastMoveMonster::stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField) {
	if (counter < 7)
	{
		NormalMoveMonster nextstate;
		nextstate.stateDetermination(counter, monster, hero, gameField);
		previousState();
	}
	else { moveTowardsHero(monster, hero, gameField); }
}

void FastMoveMonster::previousState() {
	monster->setMonsterState(new NormalMoveMonster());
}

void FastMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField){
	bool moveIsMade = false;
	int deltaX = monster.getPosition().x - hero.getPosition().x;
	int deltaY = monster.getPosition().y - hero.getPosition().y;
	while (!moveIsMade) {
		Position value;
		// –ух на дв≥ кл≥тинки Ї пр≥ор≥тетним
		if (std::abs(deltaX) > 2) {
			value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -2 : (deltaX < -1) ? 2 : 0), monster.getPosition().y);
			if (gameField->freeCell(value)) {
				gameField->eraseContent(monster.getPosition()); // erase the cell
				monster.setPosition(value);

				gameField->moveHero(value);
				moveIsMade = true;
			}
		}
		else if (std::abs(deltaY) > 2) {
			value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -2 : (deltaY < -1) ? 2 : 0));
			if (gameField->freeCell(value)) {
				gameField->eraseContent(monster.getPosition()); // erase the cell
				monster.setPosition(value);

				gameField->moveHero(value);
				moveIsMade = true;
			}
		}
		else {
			if ((std::abs(deltaX) >= 2) || (std::abs(deltaY) >= 2)) {
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
				//’одимо по X
				value.setCoordinates(monster.getPosition().x + ((deltaX > 1) ? -1 : (deltaX < -1) ? 1 : 0), monster.getPosition().y);

				if (gameField->freeCell(value)) {
					gameField->eraseContent(monster.getPosition()); // erase the cell
					monster.setPosition(value);

					gameField->moveHero(value);
					moveIsMade = true;
				}
				else if (deltaY != 0) {
					// якщо рух по X неможливий, але можна по Y
					value.setCoordinates(monster.getPosition().x, monster.getPosition().y + ((deltaY > 1) ? -1 : (deltaY < -1) ? 1 : 0));
					if (gameField->freeCell(value)) {
						gameField->eraseContent(monster.getPosition()); // erase the cell
						monster.setPosition(value);

						gameField->moveHero(value);
						moveIsMade = true;
					}
				}
			}
		}
	}
}