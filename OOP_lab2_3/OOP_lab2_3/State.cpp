#include "State.h"
#include "Monster.h"

void State::setStateForMonster(Monster* value) {
	monster = value;
}

void State::nextState() {}

void State::previousState() {}

State::~State() {}