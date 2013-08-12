#pragma once
#include "Circle.h"
#include "SFML\Graphics.hpp"

class Planet :
	public Circle
{
public:
	Planet(sf::Vector2f position, float radius, sf::Color color): Circle(position, radius, color) 
	{
		
	};
	~Planet(void);

	void update(float deltaTime);

private:

};