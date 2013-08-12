#include "GameScreen.h"

GameScreen::GameScreen(void)
{

}

int GameScreen::run(sf::RenderWindow &window)
{
	float viewSpeed = 1000.0f;

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event event;
	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
	
	bool running = true;

	Player player;
	Level level(sf::Vector2i(5000, 5000), 350, 20, 50);
	view.reset(sf::FloatRect(sf::Vector2f(level.getDimension()/2), windowSize));

	while(true == running)
	{
		deltaTime = clock.restart().asSeconds();
		//std::cout << deltaTime << std::endl;

		//event management
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
		}

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

		updateView(level);

		//draw management
		window.clear();
		window.setView(view);
		level.draw(window);
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

	if(viewCenter.x - .5 * viewSize.x < 0)
		newCenter.x = .5 * viewSize.x;
	if(viewCenter.y - .5 * viewSize.y < 0)
		newCenter.y = .5 * viewSize.y;
	if(viewCenter.x + .5 * viewSize.x > dimension.x)
		newCenter.x = dimension.x - .5 * viewSize.x;
	if(viewCenter.y + .5 * viewSize.x > dimension.y)
		newCenter.y = dimension.y - .5 * viewSize.x;

	view.setCenter(newCenter);
}