/**
* @file Game.h
* @brief The main game class header
* @author Dylan Manley & Jakub Stepien
*/

#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tile.h"
#include "MiniMax.h"

/**
* @enum GameState
* @brief Represents the different states of the game
*/
enum class GameState
{
	PLACING,
	PLAYING,
	ENDED
};

/**
* @class Game
* @brief The main game class that handles the game loop and logic
*/
class Game
{
public:
	/** @brief Constructor - initializes game */
	Game();

	/** @brief Destructor */
	~Game();

	/** @brief Main game loop running at 60 FPS */
	void run();

private:
	/** @brief Process window events */
	void processEvents();

	/** @brief Process key presses
	 *  @param t_event Key press event */
	void processKeys(const std::optional<sf::Event> t_event);

	/** @brief Check keyboard state */
	void checkKeyboardState();

	/** @brief Update game logic
	 *  @param t_deltaTime Time since last update */
	void update(sf::Time t_deltaTime);

	/** @brief Render all game elements */
	void render();

	/** @brief Show possible moves for selected piece
	 *  @return Number of valid moves */
	int showPossibleMoves();

	/** @brief Check for win condition */
	void checkForWin();

	/** @brief Initialize text elements */
	void setupTexts();

	/** @brief Initialize sprites */
	void setupSprites();

	/** @brief Initialize audio */
	void setupAudio();

	/** @brief Initialize game grid */
	void setupGrid();

	/** @brief Clear all move indicators */
	void clearMoves();
	
	sf::RenderWindow m_window;  ///< Main window
	sf::Font m_jerseyFont;      ///< UI font
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; // text used for message on screen
	sf::Texture m_DELETElogoTexture;//  texture used for sfml logo
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; // sprite used for sfml logo

	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game

	GameState gameState;  ///< Current game state

	static const int GRID_SIZE = 25;  ///< 5x5 grid
	Tile grid[GRID_SIZE];  ///< Game board tiles

	float xPos = 2;
	float yPos = 5;

	bool playerTurn = true;     ///< True if player's turn
	int placedPieces = 0;    ///< Number of pieces placed

	sf::Texture snakeTex;
	sf::Texture frogTex;
	sf::Texture donkeyTex;

	sf::Vector2i mousePos;
	sf::Vector2f boardPos;

	Snake snake;         ///< Player snake
	Frog frog;           ///< Player frog
	Donkey donkey[3];    ///< Player donkeys

	Snake aiSnake;       ///< AI snake
	Frog aiFrog;         ///< AI frog
	Donkey aiDonkey[3];  ///< AI donkeys

	pieces* selectedPiece;  ///< Currently selected piece

	MiniMax ai;  ///< AI controller

	bool singleClick;  ///< Click limiter

	sf::Text depthText{m_jerseyFont};
};

#pragma warning( pop ) 
#endif // !GAME_HPP

