#pragma once
#include "Character.h"
#include "Hero.h"

class Archer : public Hero{
public:
	Archer() noexcept;
	~Archer();
	void move(Position newCoordinates, Field* gameField);
	void attack(Monster& target, Field* gameField);
};