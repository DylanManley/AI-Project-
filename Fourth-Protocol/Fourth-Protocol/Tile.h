#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	~Tile();

	void update();
	void render(sf::RenderWindow& t_window);
	
	void setup();
	bool isHovered(sf::Vector2f t_mousePos);
	bool isOccupied();
	bool isPossibleMove();

	void setPosition(sf::Vector2f t_position);
	void setColour(sf::Color t_colour);
	void setOccupied(bool t_occupied);
	void setPossibleMove(bool t_possibleMove);

	sf::Vector2f getPosition();


private:
	sf::RectangleShape shape;

	bool occupied = false;
	bool possibleMove = false;
};