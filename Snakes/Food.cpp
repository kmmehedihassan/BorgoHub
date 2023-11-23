#include "Food.h"

Food::Food(std::pair<int, int> pos) :position(pos)
{
	points = (rand() % 3 + 1) * 10;
	color = sf::Color::Red;
}

std::pair<int, int> Food::getPosition()
{
	return position;
}

int Food::getPoints()
{
	return points;
}

sf::Color Food::getColor()
{
	return color;
}

std::set<std::pair<int, int>> Food::getFoodPosition()
{
	std::set<std::pair<int, int>> ret;
	ret.insert(getPosition());
	return ret;
}

std::map<std::pair<int, int>, sf::Color> Food::getFoodColor()
{
	std::map<std::pair<int, int>, sf::Color> ret;
	ret[getPosition()] = getColor();
	return ret;
}
