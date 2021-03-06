#pragma once
#include "Screen.h"
#include <iostream>
#include "Player.h"
#include "Level.h"

class GameScreen :
	public Screen
{
public:
	GameScreen(void);
	virtual int run(sf::RenderWindow& window);
	void update(float deltaTime);

private:
	sf::View view;

	void updateView(Level& level);
};