#include "Pieces.h"

void pieces::setUp(sf::Texture &texture, sf::Vector2f position, PieceType t_type, bool ai)
{
    type = t_type;
	aiControlled = ai;
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

int pieces::SetMoves(Tile grid[], int index, int jumpOffset)
{
    int count = 0;
    if (index >= 0 && index < 25)
    {
        if (!grid[index].isOccupied())
        {
            grid[index].setPossibleMove(true);
            count++;
        }
        else if (jumpOffset != 0)
        {
            int jumpIndex = index + jumpOffset;

			int fromRow = index / 5;
			int fromCol = index % 5;
			int toRow = jumpIndex / 5;
			int toCol = jumpIndex % 5;

			int rowDiff = toRow - fromRow;
			int colDiff = toCol - fromCol;

            if (abs(colDiff) > 2)
            {
                return 0;
            }

            if (jumpIndex >= 0 && jumpIndex < 25 
                && !grid[jumpIndex].isOccupied() )
            {
                grid[jumpIndex].setPossibleMove(true);
                grid[jumpIndex].setColour(sf::Color(0, 0, 255, 70));
            }
        }
    }
	return count;
}

void pieces::move(sf::Vector2f position)
{
    pos = { position.x + 8, position.y + 9 };
    sprite->setPosition(pos);
    shape.setPosition(sf::Vector2f(pos.x - 5, pos.y - 5));
    if (!aiControlled)
    {
        shape.setFillColor(sf::Color::Green);
    }
    else
    {
		shape.setFillColor(sf::Color::Red);
    }
}

int pieces::getCurrentTileIndex(Tile grid[])
{
    for (int i = 0; i < 25; i++)
    {
        if (grid[i].getShape().getGlobalBounds().contains(pos))
        {
            //std::cout << std::endl;
			//std::cout << "Piece Position: (" << shape.getPosition().x << ", " << shape.getPosition().y << ")" << std::endl;
			//std::cout << "Tile Position: (" << grid[i].getPosition().x << ", " << grid[i].getPosition().y << ")" << std::endl;
			//std::cout << "Index Found: " << i << std::endl;
            return i;
        }
    }
    return -1; // Not found
}

PieceType pieces::getPieceType()
{
    return type;
}

int Donkey::showMoves(Tile grid[], int gridPos)
{
    int count = 0;
    //left
    if (gridPos % 5 != 0)
    {
        count += SetMoves(grid, gridPos - 1, 0);
    }
    // Right
    if (gridPos % 5 != 4) 
    {
        count += SetMoves(grid, gridPos + 1, 0);;
    } 
    // Up
    if (gridPos - 5 >= 0)
    {
        count += SetMoves(grid, gridPos - 5, 0);
    }   
    // Down
    if (gridPos + 5 < 25)
    {
        count += SetMoves(grid, gridPos + 5, 0);
    }

    return count;
}

int Snake::showMoves(Tile grid[], int gridPos)
{
    int count = 0;

    //left
    if (gridPos % 5 != 0)
    {
        count += SetMoves(grid, gridPos - 1, 0);
    }
    // Right
    if (gridPos % 5 != 4)
    {
        count += SetMoves(grid, gridPos + 1, 0);
    }
    // Up
    if (gridPos - 5 >= 0)
    {
        count += SetMoves(grid, gridPos - 5, 0);
    }
    // Down
    if (gridPos + 5 < 25)
    {
        count += SetMoves(grid, gridPos + 5, 0);
    }

    // Up Left
    if (gridPos % 5 != 0 && gridPos - 5 >= 0)
    {
        count += SetMoves(grid, gridPos - 6, 0);
    }
    // Up Right
    if (gridPos % 5 != 4 && gridPos - 5 >= 0)
    {
        count += SetMoves(grid, gridPos - 4, 0);
    }
    // Down Left
    if (gridPos % 5 != 0 && gridPos + 5 < 25)
    {
        count += SetMoves(grid, gridPos + 4, 0);
    }
    // Down Right
    if (gridPos % 5 != 4 && gridPos + 5 < 25)
    {
        count += SetMoves(grid, gridPos + 6, 0); 
    }

    return count;
}

int Frog::showMoves(Tile grid[], int gridPos)
{
    int count = 0;

    if (gridPos % 5 != 0) //left
    {
        count += SetMoves(grid, gridPos - 1, -1);
    }
    if (gridPos % 5 != 4) // Right
    {
        count += SetMoves(grid, gridPos + 1, 1);
    }
    if (gridPos - 5 >= 0) // Up
    {
        count += SetMoves(grid, gridPos - 5, -5);
    }
    if (gridPos + 5 < 25) // Down
    {
        count += SetMoves(grid, gridPos + 5, 5);
    }

    if (gridPos % 5 != 0 && gridPos - 5 >= 0) // Up Left
    {
        count += SetMoves(grid, gridPos - 6, -6);
    }
    if (gridPos % 5 != 4 && gridPos - 5 >= 0) // Up Right
    {
        count += SetMoves(grid, gridPos - 4, -4);
    }
    if (gridPos % 5 != 0 && gridPos + 5 < 25) // Down Left
    {
        count += SetMoves(grid, gridPos + 4, 4);
    }
    if (gridPos % 5 != 4 && gridPos + 5 < 25) // Down Right
    {
        count += SetMoves(grid, gridPos + 6, 6);
    }

    return count;
}
