#include "SFML/Graphics.hpp"
#include "Tile.h"
#include <iostream>

enum PieceType
{
    DONKEY,
    SNAKE,
    FROG
};

class pieces
{
public:
    sf::RectangleShape shape;
    sf::Sprite *sprite = nullptr;
    sf::Vector2f pos;
    bool placed = false;
    bool selected = false;
	bool aiControlled = false;
	PieceType type;

    virtual void setUp(sf::Texture& texture, sf::Vector2f position, PieceType t_type, bool ai);

    virtual void place(sf::Vector2f position);

    virtual int SetMoves(Tile grid[], int index, int jumpOffset = 0);

    virtual int showMoves(Tile grid[], int gridPos) = 0;

    virtual void move(sf::Vector2f t_position);

    virtual int getCurrentTileIndex(Tile grid[]);

    virtual PieceType getPieceType();
};

class Donkey : public pieces
{
public:
    virtual int showMoves(Tile grid[], int gridPos) override;
};

class Snake : public pieces
{
public:
    virtual int showMoves(Tile grid[], int gridPos) override;
};

class Frog : public pieces
{
public:
    virtual int showMoves(Tile grid[], int gridPos) override;
};