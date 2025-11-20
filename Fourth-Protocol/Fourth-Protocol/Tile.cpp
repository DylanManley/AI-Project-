#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderWindow& t_window)
{
	if (possibleMove)
	{
		shape.setFillColor(sf::Color(0, 0, 255, 70));
	}
	else
	{
		shape.setFillColor(sf::Color::White);
	}
	t_window.draw(shape);
}

void Tile::setup()
{
	shape.setSize(sf::Vector2f{ 100, 100 });
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);

	occupied = false;
}

void Tile::setOwner(int t_owner)
{
	owner = t_owner;
}

int Tile::getOwner()
{
	return owner;
}

bool Tile::isHovered(sf::Vector2f t_mousePos)
{
	return (shape.getGlobalBounds().contains(t_mousePos));
}

bool Tile::isOccupied()
{
	return occupied;
}

bool Tile::isPossibleMove()
{
	return possibleMove;
}

void Tile::setPosition(sf::Vector2f t_position)
{
	shape.setPosition(t_position);
}

void Tile::setColour(sf::Color t_colour)
{
	shape.setFillColor(t_colour);
}

void Tile::setOccupied(bool t_occupied)
{
	occupied = t_occupied;
}

void Tile::setPossibleMove(bool t_possibleMove)
{
	possibleMove = t_possibleMove;
}

sf::Vector2f Tile::getPosition()
{
	return shape.getPosition();
}

sf::RectangleShape Tile::getShape()
{
	return shape;
}
