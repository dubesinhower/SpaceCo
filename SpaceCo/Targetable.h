#pragma once
#include "Circle.h"
#include "SFML\Graphics.hpp"
#include <math.h>

class Targetable
{
public:
	Targetable(sf::Vector2f position, float radius, sf::Color color) : circle(position, radius)
	{
		circle.setFillColor(color);
	};
	~Targetable(void) {};

	bool isPointInside(sf::Vector2f point)
	{
		sf::Vector2f position = circle.getPosition();
		float radius = circle.getRadius();
		if(pow((position.x - point.x), 2) + pow((position.y - point.y), 2) < pow(radius, 2))
			return true;
		else
			return false;
	};
	sf::Vector2f getPosition() { return circle.getPosition(); };
	void setPosition(sf::Vector2f position) { circle.setPosition(position); };
	void offsetPosition(sf::Vector2f offsetPosition) { circle.offsetPosition(offsetPosition); };
	void draw(sf::RenderWindow& window);

protected:
	Circle circle;
};