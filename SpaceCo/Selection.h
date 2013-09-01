#pragma once
#include "SFML\System.hpp"
#include "boost\ptr_container\ptr_vector.hpp"
#include "Planet.h"

class Selection
{
public:
	Selection(void);
	~Selection(void);

	bool selectionActive() { return activeSelection; };
	sf::IntRect getSelectionBox()
	{
		int width = abs(endPosition.x - startPosition.x);
		int height = abs(endPosition.y - startPosition.y);
		sf::Vector2i topLeft;
		if(startPosition.x < endPosition.x)
			topLeft.x = startPosition.x;
		else
			topLeft.x = endPosition.x;
		if(startPosition.y < endPosition.y)
			topLeft.y = startPosition.y;
		else
			topLeft.y = endPosition.y;
		return sf::IntRect(topLeft.x, topLeft.y, width, height);
	}

private:
	bool activeSelection;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
};