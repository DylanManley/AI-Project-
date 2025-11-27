#include "MiniMax.h"
#include <iostream>

int MiniMax::getBestPlacement(Tile grid[])
{
    int bestScore = -999999;
    int bestPlacement = -1;

    for (int i = 0; i < 25; i++)
    {
        if (!grid[i].isOccupied())
        {
            grid[i].setOccupied(true);
            grid[i].setOwner(2);

            int score = evaluateBoard(grid);

            grid[i].setOccupied(false);
            grid[i].setOwner(0);

            if (score > bestScore)
            {
                bestScore = score;
                bestPlacement = i;
            }
        }
    }

    return bestPlacement;
}

Move MiniMax::getBestMove(Tile grid[], pieces* aiPieces[])
{
    Move bestMove = { -1, -1, -1, -9999 };

    for (int i = 0; i < 5; i++)
    {
        int pieceType = aiPieces[i]->getPieceType();
        int currentPos = aiPieces[i]->getCurrentTileIndex(grid);

        std::vector<int> possibleMoves = getValidMovesForPiece(grid, currentPos, pieceType);

        for (int targetPos : possibleMoves)
        {
            grid[currentPos].setOccupied(false);
            grid[currentPos].setOwner(0);
            grid[targetPos].setOccupied(true);
            grid[targetPos].setOwner(AI_PLAYER);

            int score = minimax(grid, MAX_DEPTH, false);

            grid[currentPos].setOccupied(true);
            grid[currentPos].setOwner(AI_PLAYER);
            grid[targetPos].setOccupied(false);
            grid[targetPos].setOwner(0);

            if (score > bestMove.score)
            {
                bestMove.pieceIndex = i;
                bestMove.fromTile = currentPos;
                bestMove.toTile = targetPos;
                bestMove.score = score;
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

    // Horizontal lines
    for (int row = 0; row < 5; row++)
    {
        int indices[5] = {
            row * 5 + 0,
            row * 5 + 1,
            row * 5 + 2,
            row * 5 + 3,
            row * 5 + 4
        };
        totalScore += evaluateLine(grid, indices);
    }

    // Vertical lines
    for (int col = 0; col < 5; col++)
    {
        int indices[5] = {
            0 * 5 + col,
            1 * 5 + col,
            2 * 5 + col,
            3 * 5 + col,
            4 * 5 + col
        };
        totalScore += evaluateLine(grid, indices);
    }

    // Diagonal (top-left to bottom-right)
    int diagStarts[][2] = { {0, 0}, {0, 1}, {1, 0} };
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

    // Anti-diagonal (top-right to bottom-left)
    int antiDiagStarts[][2] = { {0, 4}, {0, 3}, {1, 4} };
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

    for (int i = 0; i < 5; i++)
    {
        int owner = grid[indices[i]].getOwner();
        if (owner == 2)
            aiCount++;
        else if (owner == 1)
            playerCount++;
        else
            emptyCount++;
    }

    return scoreLine(aiCount, playerCount, emptyCount);
}

int MiniMax::scoreLine(int aiCount, int playerCount, int emptyCount)
{
    if (aiCount > 0 && playerCount > 0)
        return 0;

    if (aiCount > 0)
    {
        if (aiCount == 3) return 100000; // Win!
        if (aiCount == 2) return 75;
        if (aiCount == 1) return 10;
    }

    if (playerCount > 0)
    {
        if (playerCount == 3) return -200000; // Must block
        if (playerCount == 2) return -90;
        if (playerCount == 1) return -5;
    }

    return 0;
}

std::vector<int> MiniMax::getValidMovesForPiece(Tile grid[], int gridPos, int pieceType)
{
    // temporary piece for checking moves
    pieces* tempPiece = nullptr;

    switch (pieceType)
    {
    case DONKEY: tempPiece = new Donkey(); break;
    case SNAKE:  tempPiece = new Snake();  break;
    case FROG:   tempPiece = new Frog();   break;
    default: return {};
    }

    for (int i = 0; i < 25; ++i)
        grid[i].setPossibleMove(false);

    tempPiece->showMoves(grid, gridPos);

    std::vector<int> validMoves;
    for (int i = 0; i < 25; ++i)
    {
        if (grid[i].isPossibleMove())
            validMoves.push_back(i);
    }

    delete tempPiece;
    return validMoves;
}

int MiniMax::minimax(Tile grid[], int depth, bool isMaximizing)
{
    if (depth == 0)
    {
        return evaluateBoard(grid);
    }

    if (isMaximizing) // AI's turn
    {
        int maxEvaluation = -99999;

        for (int i = 0; i < 25; i++)
        {
            if (grid[i].isOccupied() && grid[i].getOwner() == AI_PLAYER)
            {
                std::vector<int> moves = getValidMovesForPiece(grid, i, SNAKE);

                for (int targetPos : moves)
                {
                    makeMove(grid, i, targetPos, AI_PLAYER);
                    int eval = minimax(grid, depth - 1, false);
                    undoMove(grid, i, targetPos, AI_PLAYER);

                    maxEvaluation = std::max(maxEvaluation, eval);
                }
            }
        }
        return maxEvaluation;
    }
    else
    {
        int minEvaluation = 99999;

        for (int i = 0; i < 25; i++)
        {
            if (grid[i].isOccupied() && grid[i].getOwner() == PLAYER)
            {
                std::vector<int> moves = getValidMovesForPiece(grid, i, SNAKE);

                for (int targetPos : moves)
                {
                    makeMove(grid, i, targetPos, PLAYER);
                    int eval = minimax(grid, depth - 1, true);
                    undoMove(grid, i, targetPos, PLAYER);

                    minEvaluation = std::min(minEvaluation, eval);
                }
            }
        }
        return minEvaluation;
    }
}

void MiniMax::makeMove(Tile gridCopy[], int from, int to, int player)
{
    gridCopy[from].setOccupied(false);
    gridCopy[from].setOwner(0);
    gridCopy[to].setOccupied(true);
    gridCopy[to].setOwner(player);
}

void MiniMax::undoMove(Tile gridCopy[], int from, int to, int originalOwner)
{
    gridCopy[to].setOccupied(false);
    gridCopy[to].setOwner(0);
    gridCopy[from].setOccupied(true);
    gridCopy[from].setOwner(originalOwner);
}