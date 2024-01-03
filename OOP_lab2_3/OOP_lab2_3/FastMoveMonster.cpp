#include "FastMoveMonster.h"
#include "NormalMoveMonster.h"
#include "SlowMoveMonster.h"
#include "Field.h"
#include "Position.h"

void FastMoveMonster::previousState() {
	monster->setMonsterState(new NormalMoveMonster());
}

void FastMoveMonster::moveTowardsHero(Monster& monster, Hero& hero, Field* gameField){
	bool moveIsMade = false;
	int deltaX = monster.getPosition().x - hero.getPosition().x;
	int deltaY = monster.getPosition().y - hero.getPosition().y;

}