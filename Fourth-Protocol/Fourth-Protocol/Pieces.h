#include "SFML/Graphics.hpp"
#include "Tile.h"

class pieces
{
public:
    sf::RectangleShape shape;
    sf::Sprite *sprite = nullptr;
    sf::Vector2f pos;
    bool placed = false;
    bool selected = false;

    virtual void setUp(sf::Texture& texture, sf::Vector2f position);

    virtual void place(sf::Vector2f position);

    virtual void highlightTiles(Tile grid[], int index, int jumpOffset = 0);

    virtual void showMoves(Tile grid[], int gridPos) = 0;

    virtual void move(sf::Vector2f t_position);
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