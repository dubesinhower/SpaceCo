#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "Screens.h"

int main() 
{
	std::vector<Screen*> screens;
	int currentScreen = 0;

	sf::RenderWindow window(sf::VideoMode(1440, 900, 32), "SpaceCo");

	GameScreen gs;
	screens.push_back(&gs);

   while (currentScreen >= 0)
   {
	   //switch screens based on the return int from the current screen
	   currentScreen = screens[currentScreen]->run(window);
   }

	return 0;
}