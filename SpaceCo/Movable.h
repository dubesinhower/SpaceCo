#pragma once
#include "Targetable.h"

class Movable :
	public Targetable
{
public:
	Movable(sf::Vector2f position, float radius, sf::Color color, float topSpeed, float accelerationTime) : Targetable(position, radius, color)
	{
		this->topSpeed = topSpeed;
		this->accelerationTime = accelerationTime;
		startingPosition = position;
	};
	~Movable(void) {};

	sf::Vector2f getVelocity() { return velocity; };
	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; };
	void setStartingPosition(sf::Vector2f position) { startingPosition = position; };
	void update(float deltaTime) {};

protected:
	float topSpeed;
	float accelerationTime;
	sf::Vector2f velocity;
	sf::Vector2f startingPosition;
};

