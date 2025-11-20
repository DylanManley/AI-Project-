#pragma once
#include "Pieces.h"

class MiniMax
{
public:
    int getBestPlacement(Tile grid[]);

private:
    int evaluateBoard(Tile grid[]);


    int checkAllLines(Tile grid[]);

    int scoreLine(int aiCount, int playerCount, int emptyCount);

    int evaluateLine(Tile grid[], int indices[4]);
};
