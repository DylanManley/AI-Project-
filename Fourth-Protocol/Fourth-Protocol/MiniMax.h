/**
 * @file MiniMax.h
 * @brief Minimax AI with alpha-beta pruning
 * @author Dylan Manley & Jakub Stepien
 */

#pragma once
#include "Pieces.h"

 /**
  * @struct Move
  * @brief Represents a piece movement
  */
struct Move
{
    int pieceIndex; // Index of piece to move
    int fromTile; // Current tile
	int toTile; // Target tile
	int score; // Score
};

/**
 * @class MiniMax
 * @brief AI engine using minimax algorithm
 */
class MiniMax
{
public:
    /** @brief Find best tile for initial placement
     *  @param grid Game board
     *  @return Best tile index or -1 */
    int getBestPlacement(Tile grid[]);

    /** @brief Find best move using minimax
     *  @param grid Game board
     *  @param aiPieces AI's pieces
     *  @return Best move structure */
    Move getBestMove(Tile grid[], pieces* aiPieces[]);

    /** @brief Set search depth
     *  @param depth Max ply depth (0-9) */
    void setDepth(int depth);

    /** @brief Get current search depth
     *  @return Current depth */
    int getDepth();

private:
    int maxDepth = 2;         ///< Search depth
    const int PLAYER = 1;     ///< Player ID
    const int AI_PLAYER = 2;  ///< AI ID

    /** @brief Evaluate board position
     *  @param grid Game board
     *  @return Evaluation score */
    int evaluateBoard(Tile grid[]);

    /** @brief Check all lines on board
     *  @param grid Game board
     *  @return Total score */
    int checkAllLines(Tile grid[]);

    /** @brief Score a line configuration
     *  @param aiCount AI pieces in line
     *  @param playerCount Player pieces in line
     *  @param emptyCount Empty spaces in line
     *  @return Line score */
    int scoreLine(int aiCount, int playerCount, int emptyCount);

    /** @brief Evaluate specific line
     *  @param grid Game board
     *  @param indices 5 tile indices
     *  @return Line score */
    int evaluateLine(Tile grid[], int indices[5]);

    /** @brief Get valid moves for piece
     *  @param grid Game board
     *  @param currentPos Current position
     *  @param pieceType Type of piece
     *  @return Valid move indices */
    std::vector<int> getValidMovesForPiece(Tile grid[], int currentPos, int pieceType);

    /** @brief Minimax with alpha-beta pruning
     *  @param grid Game board
     *  @param depth Remaining depth
     *  @param alpha Alpha value
     *  @param beta Beta value
     *  @param isMaximizing True for AI turn
     *  @return Best score */
    int minimax(Tile grid[], int depth, int alpha, int beta, bool isMaximizing);

    /** @brief Apply move to board
     *  @param gridCopy Board to modify
     *  @param from Source tile
     *  @param to Destination tile
     *  @param player Player ID */
    void makeMove(Tile gridCopy[], int from, int to, int player);

    /** @brief Undo move on board
     *  @param gridCopy Board to modify
     *  @param from Source tile
     *  @param to Destination tile
     *  @param originalOwner Original owner */
    void undoMove(Tile gridCopy[], int from, int to, int originalOwner);
    
};
