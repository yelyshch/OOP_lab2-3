#pragma once
#include "Character.h"
#include "Hero.h"

class Swordsman : public Hero{
private:

public:
	Swordsman() noexcept;
	int move(Position newCoordinates, Field* gameField) override;
	void attack(Monster& target, Field* gameField);
}; 
