#pragma once
#include "Selection.h"
#include "Planet.h"
#include "Level.h"
#include <boost\ptr_container\ptr_vector.hpp>
#include <boost\math\constants\constants.hpp>
#include <iostream>
#include <math.h>

class Player
{
public:
	Player(std::string name);
	~Player(void);
	
	//public interface
	void update(float deltaTime, Level level, sf::Vector2i mousePosition);
	std::string getName() { return name; };


private:
	std::string name;
	int credits;
	Selection selection;
	//members
};