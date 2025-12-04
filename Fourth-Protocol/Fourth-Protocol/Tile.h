/**
 * @file Tile.h
 * @brief Game board tile class
 * @author Dylan Manley & Jakub Stepien
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

 /**
  * @class Tile
  * @brief Represents one square on the game board
  */
class Tile
{
public:
    /** @brief Constructor */
    Tile();

    /** @brief Destructor */
    ~Tile();

    /** @brief Update tile state */
    void update();

    /** @brief Render tile to window
     *  @param t_window Target window */
    void render(sf::RenderWindow& t_window);

    /** @brief Initialize tile properties */
    void setup();

    /** @brief Check if mouse is over tile
     *  @param t_mousePos Mouse position
     *  @return True if hovering */
    bool isHovered(sf::Vector2f t_mousePos);

    /** @brief Check if tile has piece
     *  @return True if occupied */
    bool isOccupied();

    /** @brief Check if tile is valid move
     *  @return True if possible move */
    bool isPossibleMove();

    /** @brief Set tile position
     *  @param t_position New position */
    void setPosition(sf::Vector2f t_position);

    /** @brief Set tile color
     *  @param t_colour New color */
    void setColour(sf::Color t_colour);

    /** @brief Set occupied state
     *  @param t_occupied Occupied flag */
    void setOccupied(bool t_occupied);

    /** @brief Set possible move flag
     *  @param t_possibleMove Move flag */
    void setPossibleMove(bool t_possibleMove);

    /** @brief Set tile owner
     *  @param t_owner Owner ID (0=empty, 1=player, 2=AI) */
    void setOwner(int t_owner);

    /** @brief Get tile owner
     *  @return Owner ID */
    int getOwner();

    int owner;  ///< 0=empty, 1=player, 2=AI

    /** @brief Get tile position
     *  @return Position vector */
    sf::Vector2f getPosition();

    /** @brief Get tile shape
     *  @return Rectangle shape */
    sf::RectangleShape getShape();

private:
    sf::RectangleShape shape;   ///< Visual representation
    sf::Font font;              ///< Text font
    sf::Text ownerText{ font }; ///< Debug owner display

    bool occupied = false;      ///< Has piece on it
    bool possibleMove = false;  ///< Valid move destination
};