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

bool Tile::isHovered(sf::Vector2f t_mousePos)
{
	return (shape.getGlobalBounds().contains(t_mousePos));
}

bool Tile::isOccupied()
{
	return occupied;
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

sf::Vector2f Tile::getPosition()
{
	return shape.getPosition();
}
