#include "Pieces.h"

void pieces::setUp(sf::Texture &texture, sf::Vector2f position)
{
	pos = position;
	sprite = new sf::Sprite{ texture };
	sprite->setTexture(texture);
	sprite->setPosition(pos);

	shape.setFillColor(sf::Color::Transparent);
	shape.setSize(sf::Vector2f(90.0f, 90.0f));
	shape.setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
}

void pieces::place(sf::Vector2f position)
{
	pos = sf::Vector2f{ position.x + 8, position.y + 9 };
	sprite->setPosition(pos);
	shape.setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
	//shape.setFillColor(sf::Color::Transparent);
	placed = true;
}

void Donkey::move()
{

}

void Snake::move()
{

}

void Frog::move()
{

}
