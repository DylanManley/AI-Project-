#include "Pieces.h"

void pieces::setUp(sf::Texture &texture, sf::Vector2f position)
{
	pos = position;
	sprite = new sf::Sprite{ texture };
	sprite->setTexture(texture);
	sprite->setPosition(pos);
}

void pieces::place(sf::Vector2f position)
{
	pos = sf::Vector2f{ position.x + 8, position.y + 9 };
	sprite->setPosition(pos);
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
