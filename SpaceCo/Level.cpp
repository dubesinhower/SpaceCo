#include "Level.h"

Level::Level(sf::Vector2i dimension, int spaceBetweenPlanets, int minPlanetSize, int maxPlanetSize)
{
	this->dimension = dimension;
	std::cout << dimension.x << ", " << dimension.y << std::endl;
	srand(time(0));
	generateRandomPlanets(30, spaceBetweenPlanets, minPlanetSize, maxPlanetSize);
}


Level::~Level(void)
{

}

void Level::draw(sf::RenderWindow& window)
{
	for(Planet p: planets)
	{
		p.draw(window);
	}
}

void Level::generateRandomPlanets(int newPoints, int spaceBetweenPlanets, int minPlanetSize, int maxPlanetSize)
{
	//generate planets using poisson disk sampling
	//http://devmag.org.za/2009/05/03/poisson-disk-sampling/

	planets.clear();

	int cellSize = (int)spaceBetweenPlanets/sqrt(2);
	std::cout << cellSize << std::endl;

	std::vector<std::vector<int> > grid((dimension.x/cellSize) + 1, std::vector<int> ((dimension.y/cellSize) + 1, 0));
	std::cout << grid.size() << " " << grid[0].size() << std::endl;
	std::queue<sf::Vector2i> processingPoints;
	std::vector<sf::Vector2i> finalizedPoints;

	sf::Vector2i firstPoint(std::rand() % dimension.x, std::rand() % dimension.y);
	processingPoints.push(firstPoint);
	finalizedPoints.push_back(firstPoint);
	sf::Vector2i firstPointGridPosition = getGridPositionFromPoint(firstPoint, cellSize);
	std::cout << firstPointGridPosition.x << " " << firstPointGridPosition.y << std::endl;
	grid[firstPointGridPosition.x][firstPointGridPosition.y] = 1;

	while(!processingPoints.empty() || finalizedPoints.size() == 20)
	{
		sf::Vector2i point = processingPoints.front();
		processingPoints.pop();
		for(int i = 0; i < newPoints; i++)
		{
			sf::Vector2i newPoint = generatePointAroundRadius(point, spaceBetweenPlanets);
			
			if(newPoint.x >= 0 && newPoint.y >= 0 && newPoint.x < dimension.x && newPoint.y < dimension.y && !checkIfOtherPointsAreInNeighbourhood(grid, newPoint, spaceBetweenPlanets, cellSize))
			{
				processingPoints.push(newPoint);
				finalizedPoints.push_back(newPoint);
				sf::Vector2i newPointGridPosition = getGridPositionFromPoint(newPoint, cellSize);
				std::cout << newPoint.x << " " << newPoint.y << " " << newPointGridPosition.x << " " << newPointGridPosition.y << std::endl;
				grid[newPointGridPosition.x][newPointGridPosition.y] = 1;
			}
		}
	}

	for(sf::Vector2i point: finalizedPoints)
	{
		float radius = rand() % (maxPlanetSize - minPlanetSize) + minPlanetSize;
		planets.push_back(new Planet((sf::Vector2f)point, radius, sf::Color::White));
	}

	std::cout << planets.size() << " planets created" << std::endl;
}

sf::Vector2i Level::getGridPositionFromPoint(sf::Vector2i point, int cellSize)
{
	return point / cellSize;
}

sf::Vector2i Level::generatePointAroundRadius(sf::Vector2i point, int spaceBetweenPoints)
{
	const float PI = 4.0*atan(1.0);

	float randomNum1 = (float)rand()/(float)RAND_MAX; //between 0 and 1
	float randomNum2 = (float)rand()/(float)RAND_MAX;

	float tempRadius = spaceBetweenPoints * (randomNum1 + 1);
	float tempAngle = 2 * PI * randomNum2;

	sf::Vector2i generatedPoint(point.x + tempRadius * std::cos(tempAngle) ,point.y + tempRadius * std::sin(tempAngle));
	return generatedPoint;
}

bool Level::checkIfOtherPointsAreInNeighbourhood(std::vector<std::vector<int> > grid, sf::Vector2i point, int spaceBetweenPoints, int cellSize)
{
	sf::Vector2i pointGridLocation = getGridPositionFromPoint(point, cellSize);

	std::vector<sf::Vector2i> cellsAroundPoint = getCellsAroundPoint(grid, pointGridLocation, 5);

	for(sf::Vector2i cell: cellsAroundPoint)
	{
		if(grid[cell.x][cell.y] == 1)
		{
			if(distanceToCell(point, cell, cellSize) < (float)spaceBetweenPoints)
				return true;
		}
	}

	return false;
}

std::vector<sf::Vector2i> Level::getCellsAroundPoint(std::vector<std::vector<int> > grid, sf::Vector2i pointGridLocation, int numCellsToReturn)
{
	std::vector<sf::Vector2i> cellsAroundPoint;

	int cellDistance = floor(numCellsToReturn/2);

	for(int i = pointGridLocation.x - cellDistance; i < pointGridLocation.x + cellDistance; i++)
		for(int j = pointGridLocation.y - cellDistance; j < pointGridLocation.y + cellDistance; j++)
		{
			if(i >= 0 && j >=0 && i < grid.size() && j < grid[0].size())
			{
				cellsAroundPoint.push_back(sf::Vector2i(i, j));
			}
		}
	return cellsAroundPoint;
}

float Level::distanceToCell(sf::Vector2i point, sf::Vector2i cell, int cellSize)
{
	sf::Vector2f topLeft(cell * cellSize);
	float halfCellSize = .5 * cellSize;

	sf::Vector2f cellCenter(topLeft.x + halfCellSize, topLeft.y + halfCellSize);
	
	float XToCenter = abs(point.x - cellCenter.x);
	float YToCenter = abs(point.y - cellCenter.y);

	float x = (XToCenter - halfCellSize)<0 ? 0 : XToCenter - halfCellSize;
	float y = (YToCenter - halfCellSize)<0 ? 0 : YToCenter - halfCellSize;

	return sqrt(pow(x, 2) + pow(y, 2));
}