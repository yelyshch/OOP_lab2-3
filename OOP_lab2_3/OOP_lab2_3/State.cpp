#include "State.h"
#include "Monster.h"

void State::setStateForMonster(Monster* value) {
	monster = value;
}

void State::nextState() {}

void State::previousState() {}

void State::stateDetermination(int counter, Monster& monster, Hero& hero, Field* gameField) {}

State::~State() {}