#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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
	void setOwner(int t_owner);
	int getOwner();

	int owner = 0; //0 = empty, 1 = player, 2 = AI

	sf::Vector2f getPosition();
	sf::RectangleShape getShape();


private:
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text ownerText{ font };

	bool occupied = false;
	bool possibleMove = false;
};