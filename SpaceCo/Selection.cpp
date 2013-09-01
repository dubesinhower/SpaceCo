#include "Selection.h"

Selection::Selection(void)
{
	activeSelection = false;
	startPosition = sf::Vector2f(-1, -1);
	endPosition = sf::Vector2f(-1, -1);
}

Selection::~Selection(void)
{

}

//void Selection::update(boost::ptr_vector<Planet> planets)
//{
//
//}