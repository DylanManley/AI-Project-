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

void pieces::SetMoves(Tile grid[], int index, int jumpOffset)
{
    if (index >= 0 && index < 25)
    {
        if (!grid[index].isOccupied())
        {
            grid[index].setPossibleMove(true);
            
        }
        else if (jumpOffset != 0)
        {
            /*int jumpIndex = index + jumpOffset;
            if (jumpIndex >= 0 && jumpIndex < 24 && !grid[jumpIndex].isOccupied())
            {
                grid[jumpIndex].setPossibleMove(true);
                grid[jumpIndex].setColour(sf::Color(0, 0, 255, 70));
            }*/
        }
    }
}

void pieces::move(sf::Vector2f position)
{
    pos = { position.x + 8, position.y + 9 };
    sprite->setPosition(pos);
    shape.setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
    shape.setFillColor(sf::Color::Green);
}

void Donkey::showMoves(Tile grid[], int gridPos)
{
    //left
    if (gridPos % 5 != 0) SetMoves(grid, gridPos - 1, -1);
    // Right
    if (gridPos % 5 != 4) SetMoves(grid, gridPos + 1, 1);
    // Up
    if (gridPos - 5 >= 0) SetMoves(grid, gridPos - 5, -5);
    // Down
    if (gridPos + 5 < 24) SetMoves(grid, gridPos + 5, 5);
}

void Snake::showMoves(Tile grid[], int gridPos)
{
   
    if (gridPos % 5 != 0) SetMoves(grid, gridPos - 1, -1);  //left
    if (gridPos % 5 != 4) SetMoves(grid, gridPos + 1, 1); // Right
    if (gridPos - 5 >= 0) SetMoves(grid, gridPos - 5, -5);  // Up
    if (gridPos + 5 < 24) SetMoves(grid, gridPos + 5, 5); // Down

    if (gridPos % 5 != 0 && gridPos - 5 >= 0) SetMoves(grid, gridPos - 6, -6); // Up Left
    if (gridPos % 5 != 4 && gridPos - 5 >= 0) SetMoves(grid, gridPos - 4, -4); // Up Right
    if (gridPos % 5 != 0 && gridPos + 5 < 24) SetMoves(grid, gridPos + 4, 4); // Down Left
    if (gridPos % 5 != 4 && gridPos + 5 < 24) SetMoves(grid, gridPos + 6, 6); // Down Right
}

void Frog::showMoves(Tile grid[], int gridPos)
{
    if (gridPos % 5 != 0) SetMoves(grid, gridPos - 1, -1);  //left
    if (gridPos % 5 != 4) SetMoves(grid, gridPos + 1, 1); // Right
    if (gridPos - 5 >= 0) SetMoves(grid, gridPos - 5, -5);  // Up
    if (gridPos + 5 < 24) SetMoves(grid, gridPos + 5, 5); // Down

    if (gridPos % 5 != 0 && gridPos - 5 >= 0) SetMoves(grid, gridPos - 6, -6); // Up Left
    if (gridPos % 5 != 4 && gridPos - 5 >= 0) SetMoves(grid, gridPos - 4, -4); // Up Right
    if (gridPos % 5 != 0 && gridPos + 5 < 24) SetMoves(grid, gridPos + 4, 4); // Down Left
    if (gridPos % 5 != 4 && gridPos + 5 < 24) SetMoves(grid, gridPos + 6, 6); // Down Right
}
