#pragma once
#include "Monster.h"

class State {
protected:
	Monster* monster;
public:
	virtual ~State();
	void setStateForMonster(Monster* value);
	virtual void nextState();
	virtual void previousState();
	//virtual void moveTowardsHero(Monster& monster, Hero& hero, Field* gameField);
	virtual void stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField);
};