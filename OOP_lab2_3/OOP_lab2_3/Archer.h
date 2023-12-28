#pragma once
#include "Character.h"
#include "Hero.h"

class Archer : public Hero{
public:
	Archer() noexcept;
	int move(Position newCoordinates, Field* gameField) override;
	void attack(Monster& target, Field* gameField);
};