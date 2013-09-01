#include "GameScreen.h"

GameScreen::GameScreen(void)
{

}

int GameScreen::run(sf::RenderWindow &window)
{
	float viewSpeed = 1000.0f;

	//initialize deltaTime variable and clock
	float deltaTime = 0.0f;
	sf::Clock clock;

	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

	//create test player object
	//Player player("Player One");
	//create test level object
	Level level(sf::Vector2i(10000, 10000), 300, 15, 60);

	//set the camera to the center of the level
	view.reset(sf::FloatRect(sf::Vector2f(level.getDimension()/2), windowSize));

	//screen loop starts
	bool running = true;
	sf::Event event;
	while(true == running)
	{
		deltaTime = clock.restart().asSeconds();
		//std::cout << deltaTime << std::endl;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		//sfml event management loop
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				return (-1);
			}

			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Escape:
					return (-1);
					break;
				default:
					break;
				}
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{

			}
			if(event.type == sf::Event::MouseButtonReleased)
			{

			}
		}
		//event loop finished

		//view scrolling
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view.move(sf::Vector2f(0.0f, -viewSpeed*deltaTime));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			view.move(sf::Vector2f(0.0f, viewSpeed*deltaTime));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			view.move(sf::Vector2f(-viewSpeed*deltaTime, 0.0f));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view.move(sf::Vector2f(viewSpeed*deltaTime, 0.0f));
		}

		//clamp edge of view to level
		updateView(level);

		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();
		sf::Vector2f viewTopLeft(viewCenter.x - .5 * viewSize.x, viewCenter.y - .5 * viewSize.y);
		sf::Vector2f viewBottomRight(viewCenter.x + .5 * viewSize.x, viewCenter.y + .5 * viewSize.y);

		//update the player (not necessary yet)
		//player.update(deltaTime, level, mousePosition);

		//draw objects
		window.clear();
		window.setView(view);
		level.draw(window, viewTopLeft, viewBottomRight);
		window.display();
	}

	return (-1);
}

void GameScreen::updateView(Level& level)
{
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2i dimension = level.getDimension();

	sf::Vector2f newCenter = viewCenter;	

	if(viewCenter.x - .5f * viewSize.x < 0)
		newCenter.x = .5f * viewSize.x;
	if(viewCenter.y - .5f * viewSize.y < 0)
		newCenter.y = .5f * viewSize.y;
	if(viewCenter.x + .5f * viewSize.x > dimension.x)
		newCenter.x = dimension.x - .5f * viewSize.x;
	if(viewCenter.y + .5f * viewSize.x > dimension.y)
		newCenter.y = dimension.y - .5f * viewSize.x;

	view.setCenter(newCenter);
}