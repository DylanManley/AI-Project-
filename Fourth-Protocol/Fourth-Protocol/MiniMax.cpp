#include "MiniMax.h"
#include <iostream>

int MiniMax::getBestPlacement(Tile grid[])
{
    int bestScore = -999999;
    int bestMove = -1;

    // Try each empty position
    for (int i = 0; i < 25; i++)
    {
        if (!grid[i].isOccupied())
        {
            grid[i].setOccupied(true);
            grid[i].setOwner(2); // 2 = AI

            // Evaluate this position
            int score = evaluateBoard(grid);

            // Undo the move
            grid[i].setOccupied(false);
            grid[i].setOwner(0);

            // Track best move
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int MiniMax::evaluateBoard(Tile grid[])
{
    return checkAllLines(grid);
}

int MiniMax::checkAllLines(Tile grid[])
{
    int totalScore = 0;

    // Check all horizontal lines
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 1; col++)
        {
            int indices[5] = {
                row * 5 + col,
                row * 5 + col + 1,
                row * 5 + col + 2,
                row * 5 + col + 3,
                row * 5 + col + 4
            };
            totalScore += evaluateLine(grid, indices);
        }
    }

    // Check all vertical lines
    for (int col = 0; col < 5; col++)
    {
        for (int row = 0; row < 1; row++)
        {
            int indices[5] = {
                (row + 0) * 5 + col,
                (row + 1) * 5 + col,
                (row + 2) * 5 + col,
                (row + 3) * 5 + col,
                (row + 4) * 5 + col
            };
            totalScore += evaluateLine(grid, indices);
        }
    }

    // Check all diagonal lines (top-left to bottom-right)
    int diagStarts[][2] = {
        {0, 0}, {0, 1},
        {1, 0}          
    };

    for (int i = 0; i < 3; i++)
    {
        int startRow = diagStarts[i][0];
        int startCol = diagStarts[i][1];

        int indices[5] = {
            (startRow + 0) * 5 + (startCol + 0),
            (startRow + 1) * 5 + (startCol + 1),
            (startRow + 2) * 5 + (startCol + 2),
            (startRow + 3) * 5 + (startCol + 3),
            (startRow + 4) * 5 + (startCol + 4)
        };
        totalScore += evaluateLine(grid, indices);
    }

    // Check all diagonal lines (top right - bottom left)
    int antiDiagStarts[][2] = {
        {0, 4}, {0, 3},
        {1, 4}         
    };

    for (int i = 0; i < 3; i++)
    {
        int startRow = antiDiagStarts[i][0];
        int startCol = antiDiagStarts[i][1];

        int indices[5] = {
            (startRow + 0) * 5 + (startCol - 0),
            (startRow + 1) * 5 + (startCol - 1),
            (startRow + 2) * 5 + (startCol - 2),
            (startRow + 3) * 5 + (startCol - 3),
            (startRow + 4) * 5 + (startCol - 4)
        };
        totalScore += evaluateLine(grid, indices);
    }

    return totalScore;
}

int MiniMax::evaluateLine(Tile grid[], int indices[5])
{
    int aiCount = 0;
    int playerCount = 0;
    int emptyCount = 0;

    // Count pieces in this line
    for (int i = 0; i < 5; i++)
    {
        int owner = grid[indices[i]].getOwner();
        if (owner == 2) // AI
            aiCount++;
        else if (owner == 1) // Player
            playerCount++;
        else // Empty
            emptyCount++;
    }

    return scoreLine(aiCount, playerCount, emptyCount);
}

int MiniMax::scoreLine(int aiCount, int playerCount, int emptyCount)
{
    // If both players have pieces in this line, skip it
    if (aiCount > 0 && playerCount > 0)
        return 0;

    // Score AI opportunities
    if (aiCount > 0)
    {
        if (aiCount == 4) return 700;
        if (aiCount == 3) return 400;  
        if (aiCount == 2) return 75; 
        if (aiCount == 1) return 10;   
    }

    // Score blocking player threats
    if (playerCount > 0)
    {
        if (playerCount == 4) return 1200;
        if (playerCount == 3) return 1000;  // Block
        if (playerCount == 2) return 90;  
        if (playerCount == 1) return 5;
    }

    return 0;
}