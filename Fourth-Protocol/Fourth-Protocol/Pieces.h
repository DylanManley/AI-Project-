#include "SFML/Graphics.hpp"

class pieces
{
public:
    sf::Sprite *sprite = nullptr;
    sf::Vector2f pos;
    bool placed = false;
    bool selected = false;

    virtual void setUp(sf::Texture& texture, sf::Vector2f position);

    virtual void place(sf::Vector2f position);

    virtual void move() = 0;
};

class Donkey : public pieces
{
public:

	void move() override;
};

class Snake : public pieces
{
	void move() override;
};

class Frog : public pieces
{
	void move() override;
};