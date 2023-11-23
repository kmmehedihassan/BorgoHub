#include "SnakeBody.h"

SnakeBody::SnakeBody(std::pair<int, int> pos, TransformDirection dir) :position(pos), direction(dir)
{
	color = sf::Color::Yellow;
}

std::pair<int, int> SnakeBody::getPosition()
{
	return position;
}

TransformDirection SnakeBody::getDirection()
{
	return direction;
}

sf::Color SnakeBody::getColor()
{
	return color;
}

void SnakeBody::setDirection(TransformDirection dir)
{
	direction = dir;
}

void SnakeBody::setPosition(std::pair<int, int> pos)
{
	position = pos;
}
