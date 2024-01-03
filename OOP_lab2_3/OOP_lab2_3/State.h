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
};