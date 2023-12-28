#pragma once
#include "Monster.h"

class State {
protected:
	Monster* monster;
public:
	virtual ~State() = default; // деструктор
	void setStateForMonster(Monster* value) {
		monster = value;
	}
	virtual void nextState() = 0;
	virtual void previousState() = 0;
	virtual void move(Monster* walkMonster) = 0;
};