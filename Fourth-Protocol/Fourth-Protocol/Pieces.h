/**
 * @file Pieces.h
 * @brief Game piece classes and movement logic
 * @author Dylan Manley & Jakub Stepien
 */

#include "SFML/Graphics.hpp"
#include "Tile.h"
#include <iostream>

 /**
  * @enum PieceType
  * @brief Types of game pieces
  */
enum PieceType
{
    DONKEY,
    SNAKE,
    FROG
};

/**
 * @class pieces
 * @brief Base class for all game pieces
 */
class pieces
{
public:
    sf::RectangleShape shape;  ///< Visual outline
    sf::Sprite* sprite;        ///< Piece image
    sf::Vector2f pos;          ///< Current position
    bool placed;               ///< Has been placed on board
    bool selected;             ///< Currently selected
    bool aiControlled;         ///< Controlled by AI
    PieceType type;            ///< Type of piece

    /** @brief Initialize piece
     *  @param texture Piece texture
     *  @param position Starting position
     *  @param t_type Piece type
     *  @param ai True if AI controlled */
    virtual void setUp(sf::Texture& texture, sf::Vector2f position, PieceType t_type, bool ai);

    /** @brief Place piece on board
     *  @param position Board position */
    virtual void place(sf::Vector2f position);

    /** @brief Mark valid moves on grid
     *  @param grid Game board
     *  @param index Tile index to check
     *  @param jumpOffset Jump distance (for Frog)
     *  @return Number of valid moves */
    virtual int SetMoves(Tile grid[], int index, int jumpOffset = 0);

    /** @brief Show all valid moves
     *  @param grid Game board
     *  @param gridPos Current tile index
     *  @return Number of valid moves */
    virtual int showMoves(Tile grid[], int gridPos) = 0;

    /** @brief Move piece to position
     *  @param t_position Target position */
    virtual void move(sf::Vector2f t_position);

    /** @brief Get current tile index
     *  @param grid Game board
     *  @return Tile index or -1 */
    virtual int getCurrentTileIndex(Tile grid[]);

    /** @brief Get piece type
     *  @return Piece type enum */
    virtual PieceType getPieceType();
};

/**
 * @class Donkey
 * @brief Moves 1 square orthogonally (up/down/left/right)
 */
class Donkey : public pieces
{
public:
    /** @brief Show orthogonal moves
     *  @param grid Game board
     *  @param gridPos Current position
     *  @return Number of moves */
    virtual int showMoves(Tile grid[], int gridPos) override;
};

/**
 * @class Snake
 * @brief Moves 1 square in any direction (8 directions)
 */
class Snake : public pieces
{
public:
    /** @brief Show all adjacent moves
     *  @param grid Game board
     *  @param gridPos Current position
     *  @return Number of moves */
    virtual int showMoves(Tile grid[], int gridPos) override;
};

/**
 * @class Frog
 * @brief Can jump over adjacent pieces
 */
class Frog : public pieces
{
public:
    /** @brief Show moves with jumping
     *  @param grid Game board
     *  @param gridPos Current position
     *  @return Number of moves */
    virtual int showMoves(Tile grid[], int gridPos) override;
};