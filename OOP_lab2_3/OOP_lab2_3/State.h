#pragma once
#include "Monster.h"

class State {
protected:
	Monster* monster;
	bool movedAlongX = false; // ��� �������������, �� ��� ������� ��� ������ �� X
	bool movedAlongY = false;
public:
	virtual ~State();
	void setStateForMonster(Monster* value);
	virtual void nextState();
	virtual void previousState();
	virtual void stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField);
};