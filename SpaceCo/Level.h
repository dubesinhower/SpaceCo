#pragma once
#include <SFML\Graphics.hpp>
#include <boost\ptr_container\ptr_vector.hpp>
#include <boost\ptr_container\ptr_list.hpp>
#include "Planet.h"
#include "Selection.h"
#include <vector>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdlib>

class Level
{
public:
	Level(sf::Vector2i dimensions, int spaceBetweenPlanets, int minPlanetSize, int maxPlanetSize);
	~Level(void);

	sf::Vector2i getDimension() { return dimension; };
	boost::ptr_vector<Planet> getPlanetReferences() { return planets; };
	void draw(sf::RenderWindow& window, sf::Vector2f viewTopLeft, sf::Vector2f viewBottomRight);

private:
	sf::Vector2i dimension;
	boost::ptr_vector<Planet> planets;
	Selection selection;

	void generateRandomPlanets(int numberOfPlanets, int spaceBetweenPlanets, int minPlanetSize, int maxPlanetSize);

	sf::Vector2i getGridPositionFromPoint(sf::Vector2i point, int cellSize);
	sf::Vector2i generatePointAroundRadius(sf::Vector2i point, int spaceBetweenPoints);
	bool checkIfOtherPointsAreInNeighbourhood(std::vector<std::vector<int> > grid, sf::Vector2i, int spaceBetweenPoints, int cellSize);
	std::vector<sf::Vector2i> getCellsAroundPoint(std::vector<std::vector<int> > grid, sf::Vector2i pointGridLocation, int numCellsToReturn);
	float distanceToCell(sf::Vector2i point, sf::Vector2i cell, int cellSize);
};