/// <summary>
/// author Dylan Manley
/// </summary>
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
#include "Pieces.h"
#include "Tile.h"

enum class GameState
{
	PLACING,
	PLAYING
};

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();

	void showPossibleMoves(int t_pieceType);
	
	void setupTexts();
	void setupSprites();
	void setupAudio();
	void setupGrid();
	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; // text used for message on screen
	sf::Texture m_DELETElogoTexture;//  texture used for sfml logo
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; // sprite used for sfml logo

	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game

	GameState gameState = GameState::PLACING;

	static const int GRID_SIZE = 25;
	Tile grid[GRID_SIZE];

	float xPos = 2;
	float yPos = 5;

	bool playerTurn = true;
	int placedPieces = 0;

	sf::Texture snakeTex;
	sf::Texture frogTex;
	sf::Texture donkeyTex;

	sf::Vector2i mousePos;
	sf::Vector2f boardPos;

	Snake snake;
	Frog frog;
	Donkey donkey[3];

	Snake aiSnake;
	Frog aiFrog;
	Donkey aiDonkey[3];

	pieces* selectedPiece = nullptr;
};

#pragma warning( pop ) 
#endif // !GAME_HPP

