#pragma once
#include "Pieces.h"

struct Move
{
    int pieceIndex; // Index of piece to move
    int fromTile; // Current tile
	int toTile; // Target tile
	int score; // Score
};

class MiniMax
{
public:
    int getBestPlacement(Tile grid[]);

	Move getBestMove(Tile grid[], pieces* aiPieces[]);

private:
	const int MAX_DEPTH = 2;
    const int PLAYER = 1;
    const int AI_PLAYER = 2;

    int evaluateBoard(Tile grid[]);

    int checkAllLines(Tile grid[]);

    int scoreLine(int aiCount, int playerCount, int emptyCount);

    int evaluateLine(Tile grid[], int indices[5]);

    std::vector<int> getValidMovesForPiece(Tile grid[], int currentPos, int pieceType);

	int minimax(Tile grid[], int depth, int alpha, int beta, bool isMaximizing);

    void makeMove(Tile gridCopy[], int from, int to, int player);
    void undoMove(Tile gridCopy[], int from, int to, int originalOwner);
};
