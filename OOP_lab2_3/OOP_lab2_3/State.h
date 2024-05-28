#pragma once
#include "Monster.h"

class State {
protected:
	Monster* monster;
	bool movedAlongX = false; // ўоб в≥дсл≥дковувати, чи був останн≥й рух вздовж ос≥ X
	bool movedAlongY = false;
public:
	virtual ~State();
	void setStateForMonster(Monster* value);
	virtual void nextState();
	virtual void previousState();
	virtual void stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField);
};