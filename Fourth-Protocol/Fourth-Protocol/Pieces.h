#include "SFML/Graphics.hpp"
#include "Tile.h"
#include <iostream>

class pieces
{
public:
    sf::RectangleShape shape;
    sf::Sprite *sprite = nullptr;
    sf::Vector2f pos;
    bool placed = false;
    bool selected = false;
	bool aiControlled = false;

    virtual void setUp(sf::Texture& texture, sf::Vector2f position, bool ai);

    virtual void place(sf::Vector2f position);

    virtual void SetMoves(Tile grid[], int index, int jumpOffset = 0);

    virtual void showMoves(Tile grid[], int gridPos) = 0;

    virtual void move(sf::Vector2f t_position);

    virtual int getCurrentTileIndex(Tile grid[]);
};

class Donkey : public pieces
{
public:
    virtual void showMoves(Tile grid[], int gridPos) override;
};

class Snake : public pieces
{
public:
    virtual void showMoves(Tile grid[], int gridPos) override;
};

class Frog : public pieces
{
public:
    virtual void showMoves(Tile grid[], int gridPos) override;
};