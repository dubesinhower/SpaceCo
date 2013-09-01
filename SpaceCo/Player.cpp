#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
	this->name = name;
}

Player::~Player(void)
{

}

void Player::update(float deltaTime, Level level, sf::Vector2i mousePosition)
{

}