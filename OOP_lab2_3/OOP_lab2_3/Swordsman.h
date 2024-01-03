#pragma once
#include "Character.h"
#include "Hero.h"

class Swordsman : public Hero{
private:

public:
	Swordsman() noexcept;
	~Swordsman();
	int move(Position newCoordinates, Field* gameField);
	void attack(Monster& target, Field* gameField);
}; 
