/**
 * @file Game.cpp
 * @brief Game class implementation
 * @author Dylan Manley & Jakub Stepien
 */

#include "Game.h"
#include <iostream>

 /**
  * @brief Constructor initializes window and loads resources
  */
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{500, 600}, 32U }, "The Fourth Protocol" },
	m_DELETEexitGame{false} //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
	setupGrid();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/**
 * @brief Main loop running at 60 FPS with fixed timestep
 */
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	srand(time(nullptr));
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// </summary>
void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (newEvent->is<sf::Event::MouseButtonReleased>()) // user let go of left click
		{
			singleClick = true;
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
	if (playerTurn)
	{
		if (sf::Keyboard::Key::Num0 == newKeypress->code)
		{
			ai.setDepth(0);
		}
		else if (sf::Keyboard::Key::Num1 == newKeypress->code)
		{
			ai.setDepth(1);
		}
		else if (sf::Keyboard::Key::Num2 == newKeypress->code)
		{
			ai.setDepth(2);
		}
		else if (sf::Keyboard::Key::Num3 == newKeypress->code)
		{
			ai.setDepth(3);
		}
		else if (sf::Keyboard::Key::Num4 == newKeypress->code)
		{
			ai.setDepth(4);
		}
		else if (sf::Keyboard::Key::Num5 == newKeypress->code)
		{
			ai.setDepth(5);
		}
		else if (sf::Keyboard::Key::Num6 == newKeypress->code)
		{
			ai.setDepth(6);
		}
		else if (sf::Keyboard::Key::Num7 == newKeypress->code)
		{
			ai.setDepth(7);
		}
		else if (sf::Keyboard::Key::Num8 == newKeypress->code)
		{
			ai.setDepth(8);
		}
		else if (sf::Keyboard::Key::Num9 == newKeypress->code)
		{
			ai.setDepth(9);
		}
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	mousePos = sf::Mouse::getPosition(m_window);
	boardPos = m_window.mapPixelToCoords(mousePos);

	if (gameState == GameState::PLACING) // Placing Pieces
	{
		if (playerTurn) // Player Turn
		{
			for (int i = 0; i < GRID_SIZE; i++)
			{
				if (grid[i].isHovered(boardPos))
				{
					grid[i].setColour(sf::Color(0, 255, 0, 120));
				}
				else
				{
					grid[i].setColour(sf::Color::White);
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && singleClick == true)
			{
				singleClick = false;
				if (!selectedPiece)
				{
					if (!snake.placed && snake.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &snake;
						snake.selected = true;
						snake.shape.setFillColor(sf::Color::Green);
						return;
					}
					if (!frog.placed && frog.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &frog;
						frog.selected = true;
						frog.shape.setFillColor(sf::Color::Green);
						return;
					}
					for (int i = 0; i < 3; i++)
					{
						if (!donkey[i].placed && donkey[i].sprite->getGlobalBounds().contains(boardPos))
						{
							selectedPiece = &donkey[i];
							donkey[i].selected = true;
							donkey[i].shape.setFillColor(sf::Color::Green);
							return;
						}
					}
				}

				if (selectedPiece)
				{
					for (int i = 0; i < GRID_SIZE; i++)
					{
						if (grid[i].isHovered(boardPos) && !grid[i].isOccupied())
						{
							grid[i].setOccupied(true);
							grid[i].setOwner(1);
							selectedPiece->place(grid[i].getPosition());
							selectedPiece->selected = false;
							selectedPiece = nullptr;
							playerTurn = false;
							placedPieces++;
							checkForWin();
							return;
						}
					}
				}
			}
		}
		else // AI Turn
		{
			int bestTile = ai.getBestPlacement(grid);

			if (bestTile != -1) 
			{
				int pieceChoice = rand() % 3 + 1;

				switch (pieceChoice)
				{
				case 1:
					if (!aiSnake.placed)
					{
						selectedPiece = &aiSnake;
						aiSnake.shape.setFillColor(sf::Color::Red);
					}
					break;
				case 2:
					if (!aiFrog.placed)
					{
						selectedPiece = &aiFrog;
						aiFrog.shape.setFillColor(sf::Color::Red);
					}
					break;
				case 3:
					for (int i = 0; i < 3; i++)
					{
						if (!aiDonkey[i].placed)
						{
							selectedPiece = &aiDonkey[i];
							aiDonkey[i].shape.setFillColor(sf::Color::Red);
							break;
						}
					}
					break;
				default:
					break;
				}

				if (selectedPiece)
				{
					grid[bestTile].setOccupied(true);
					grid[bestTile].setOwner(2); // AI is player 2
					selectedPiece->place(grid[bestTile].getPosition());
					selectedPiece->selected = false;
					selectedPiece = nullptr;
					playerTurn = true;
					placedPieces++;
					checkForWin();
					return;
				}
			}
		}

		for (int i = 0; i < 25; i++)
		{
			grid[i].update();
		}

		if (placedPieces >= 10)
		{
			gameState = GameState::PLAYING;
		}
		
	}
	else if (gameState == GameState::PLAYING) // Playing Game
	{
		if (playerTurn) // Player Turn
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && singleClick == true)
			{
				singleClick = false;
				if (!selectedPiece)
				{
					if (snake.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &snake;
						snake.selected = true;
						snake.shape.setFillColor(sf::Color::Blue);

						if (showPossibleMoves() > 0)// Show moves for snake
						{
							return;
						}
						else
						{
							selectedPiece = nullptr;
							snake.selected = false;
							snake.shape.setFillColor(sf::Color::Green);
							return;
						}
					}
					if (frog.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &frog;
						frog.selected = true;
						frog.shape.setFillColor(sf::Color::Blue);

						if (showPossibleMoves() > 0)// Show moves for frog
						{
							return;
						}
						else
						{
							selectedPiece = nullptr;
							frog.selected = false;
							frog.shape.setFillColor(sf::Color::Green);
							return;
						}
					}
					for (int i = 0; i < 3; i++)
					{
						if (donkey[i].sprite->getGlobalBounds().contains(boardPos))
						{
							selectedPiece = &donkey[i];
							donkey[i].selected = true;
							donkey[i].shape.setFillColor(sf::Color::Blue);

							if (showPossibleMoves() > 0)// Show moves for donkey
							{
								return;
							}
							else
							{
								selectedPiece = nullptr;
								donkey[i].selected = false;
								donkey[i].shape.setFillColor(sf::Color::Green);
								return;
							}
						}
					}
				}
				else
				{
					int currentTileIndex = selectedPiece->getCurrentTileIndex(grid);
					grid[currentTileIndex].setOccupied(false);
					grid[currentTileIndex].setOwner(0);
					for (int i = 0; i < GRID_SIZE; i++)
					{
						if (grid[i].isHovered(boardPos) && grid[i].isPossibleMove())
						{							
							selectedPiece->move(grid[i].getPosition());
							grid[i].setOccupied(true);
							grid[i].setOwner(1);
							selectedPiece->selected = false;
							selectedPiece = nullptr;
							clearMoves();
							playerTurn = false;
							checkForWin();
							break;
						}
					}
				}
			}
		}
		else // AI Turn
		{
			pieces* aiPieces[5] = { &aiSnake, &aiFrog, &aiDonkey[0], &aiDonkey[1], &aiDonkey[2] };

			Move bestMove = ai.getBestMove(grid, aiPieces);

			if (bestMove.toTile != 1)
			{
				selectedPiece = aiPieces[bestMove.pieceIndex];

				grid[bestMove.fromTile].setOccupied(false);
				grid[bestMove.fromTile].setOwner(0);
				grid[bestMove.toTile].setOccupied(true);
				grid[bestMove.toTile].setOwner(2); // AI is player 2

				selectedPiece->move(grid[bestMove.toTile].getPosition());
				selectedPiece->shape.setFillColor(sf::Color::Red);
				selectedPiece = nullptr;
				checkForWin();
				playerTurn = true;
			}
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i].render(m_window);
	}

	m_window.draw(snake.shape);
	m_window.draw(frog.shape);
	m_window.draw(*snake.sprite);
	m_window.draw(*frog.sprite);

	for (int i = 0; i < 3; i++)
	{
		m_window.draw(donkey[i].shape);
		m_window.draw(*donkey[i].sprite);
	}

	m_window.draw(aiSnake.shape);
	m_window.draw(aiFrog.shape);
	m_window.draw(*aiSnake.sprite);
	m_window.draw(*aiFrog.sprite);
	
	for (int i = 0; i < 3; i++)
	{
		m_window.draw(aiDonkey[i].shape);
		m_window.draw(*aiDonkey[i].sprite);
	}

	depthText.setString("AI Depth: " + std::to_string(ai.getDepth()) + "\nChange depth by pressing 1-0");
	m_window.draw(depthText);

	m_window.display();
}

int Game::showPossibleMoves()
{
	int count = 0;

	int currentTileIndex = selectedPiece->getCurrentTileIndex(grid);
	count = selectedPiece->showMoves(grid, currentTileIndex);

	return count;
}

/**
 * @brief Check all lines for 4-in-a-row win condition
 */
void Game::checkForWin()
{
	// Check rows, columns, and diagonals for a win condition
	// If a player has won, set gameState to GameState::ENDED
	
	int aiCount = 0;
	int playerCount = 0;
	int emptyCount = 0;

	// Horizontal lines
	for (int row = 0; row < 5; row++)
	{
		aiCount = 0;
		playerCount = 0;
		emptyCount = 0;

		int indices[5] = {
			row * 5 + 0,
			row * 5 + 1,
			row * 5 + 2,
			row * 5 + 3,
			row * 5 + 4
		};
		for (int i = 0; i < 5; i++)
		{
			if (indices[i] < 25) // check if index is in bounds (diagonals mainly)
			{
				int owner = grid[indices[i]].getOwner();
				if (owner == 2)
				{
					aiCount++; 
					playerCount = 0;
				}
				else if (owner == 1)
				{
					playerCount++; 
					aiCount = 0;
				}
				else
				{
					emptyCount++;
					playerCount = 0; 
					aiCount = 0;
				}

				if (aiCount > 3 || playerCount > 3)
				{
					if (aiCount > 3)
					{
						std::cout << "AI Win detected! (Row)" << std::endl;
					}
					else if (playerCount > 3)
					{
						std::cout << "Player Win detected! (Row)" << std::endl;
					}
					gameState = GameState::ENDED;
					return;
				}
			}
		}
	}

	// Vertical lines
	for (int col = 0; col < 5; col++)
	{
		aiCount = 0;
		playerCount = 0;
		emptyCount = 0;

		int indices[5] = {
			0 * 5 + col,
			1 * 5 + col,
			2 * 5 + col,
			3 * 5 + col,
			4 * 5 + col
		};
		for (int i = 0; i < 5; i++)
		{
			if (indices[i] < 25) // check if index is in bounds (diagonals mainly)
			{
				int owner = grid[indices[i]].getOwner();
				if (owner == 2)
				{
					aiCount++;
					playerCount = 0;
				}
				else if (owner == 1)
				{
					playerCount++;
					aiCount = 0;
				}
				else
				{
					emptyCount++;
					playerCount = 0;
					aiCount = 0;
				}

				if (aiCount > 3 || playerCount > 3)
				{
					if (aiCount > 3)
					{
						std::cout << "AI Win detected! (Column)" << std::endl;
					}
					else if (playerCount > 3)
					{
						std::cout << "Player Win detected! (Column)" << std::endl;
					}
					gameState = GameState::ENDED;
					return;
				}
			}
		}
	}

	// Diagonal (top-left to bottom-right)
	int diagStarts[][2] = { {0, 0}, {0, 1}, {1, 0} };
	for (int i = 0; i < 3; i++)
	{
		aiCount = 0;
		playerCount = 0;
		emptyCount = 0;

		int startRow = diagStarts[i][0];
		int startCol = diagStarts[i][1];

		int indices[5] = {
			(startRow + 0) * 5 + (startCol + 0),
			(startRow + 1) * 5 + (startCol + 1),
			(startRow + 2) * 5 + (startCol + 2),
			(startRow + 3) * 5 + (startCol + 3),
			(startRow + 4) * 5 + (startCol + 4)
		};
		for (int i = 0; i < 5; i++)
		{
			if (indices[i] < 25) // check if index is in bounds (diagonals mainly)
			{
				int owner = grid[indices[i]].getOwner();
				if (owner == 2)
				{
					aiCount++;
					playerCount = 0;
				}
				else if (owner == 1)
				{
					playerCount++;
					aiCount = 0;
				}
				else
				{
					emptyCount++;
					playerCount = 0;
					aiCount = 0;
				}

				if (aiCount > 3 || playerCount > 3)
				{
					if (aiCount > 3)
					{
						std::cout << "AI Win detected! (Diag)" << std::endl;
					}
					else if (playerCount > 3)
					{
						std::cout << "Player Win detected! (Diag)" << std::endl;
					}
					gameState = GameState::ENDED;
					return;
				}
			}
		}
	}

	// Anti-diagonal (top-right to bottom-left)
	int antiDiagStarts[][2] = { {0, 4}, {0, 3}, {1, 4} };
	for (int i = 0; i < 3; i++)
	{
		aiCount = 0;
		playerCount = 0;
		emptyCount = 0;

		int startRow = antiDiagStarts[i][0];
		int startCol = antiDiagStarts[i][1];

		int indices[5] = {
			(startRow + 0) * 5 + (startCol - 0),
			(startRow + 1) * 5 + (startCol - 1),
			(startRow + 2) * 5 + (startCol - 2),
			(startRow + 3) * 5 + (startCol - 3),
			(startRow + 4) * 5 + (startCol - 4)
		};
		for (int i = 0; i < 5; i++)
		{
			if (indices[i] < 25) // check if index is in bounds (diagonals mainly)
			{
				int owner = grid[indices[i]].getOwner();
				if (owner == 2)
				{
					aiCount++;
					playerCount = 0;
				}
				else if (owner == 1)
				{
					playerCount++;
					aiCount = 0;
				}
				else
				{
					emptyCount++;
					playerCount = 0;
					aiCount = 0;
				}

				if (aiCount > 3 || playerCount > 3)
				{
					if (aiCount > 3)
					{
						std::cout << "AI Win detected! (Anti-Diag)" << std::endl;
					}
					else if (playerCount > 3)
					{
						std::cout << "Player Win detected! (Anti-Diag)" << std::endl;
					}
					gameState = GameState::ENDED;
					return;
				}
			}
		}
	}

}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("SFML Game");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	m_DELETEwelcomeMessage.setCharacterSize(96U);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);

	depthText.setFont(m_jerseyFont);
	depthText.setString("AI Depth: 2");
	depthText.setPosition(sf::Vector2f{ 10.0f, 520.0f });
	depthText.setCharacterSize(24U);
	depthText.setOutlineColor(sf::Color::Black);
	depthText.setFillColor(sf::Color::White);
	depthText.setOutlineThickness(2.0f);

}


/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{

	if (!snakeTex.loadFromFile("ASSETS\\IMAGES\\Snake.jpg"))
	{
		std::cout << "error loading snake" << std::endl;
	}

	if (!frogTex.loadFromFile("ASSETS\\IMAGES\\Frog.jpg"))
	{
		std::cout << "error loading frog" << std::endl;
	}

	if (!donkeyTex.loadFromFile("ASSETS\\IMAGES\\Donkey.jpg"))
	{
		std::cout << "error loading donkey" << std::endl;
	}

	xPos = 210;
	yPos = 500;

	snake.setUp(snakeTex, sf::Vector2f{ 10, yPos }, PieceType::SNAKE, false);
	frog.setUp(frogTex, sf::Vector2f{ 110, yPos }, PieceType::FROG, false);
	for (int i = 0; i < 3; i++)
	{
		donkey[i].setUp(donkeyTex, sf::Vector2f{xPos, yPos}, PieceType::DONKEY, false);
		xPos += 100;
	}

	xPos = -10000;
	yPos = -10000;

	aiSnake.setUp(snakeTex, sf::Vector2f{ 10, yPos }, PieceType::SNAKE, true);
	aiFrog.setUp(frogTex, sf::Vector2f{ 110, yPos }, PieceType::FROG, true);
	for (int i = 0; i < 3; i++)
	{
		aiDonkey[i].setUp(donkeyTex, sf::Vector2f{ xPos, yPos }, PieceType::DONKEY, true);
		xPos += 100;
	}

	std::cout << "sprites working" << std::endl;
}

/// <summary>
/// load sound file and assign buffers
/// </summary>
void Game::setupAudio()
{

}

void Game::setupGrid()
{
	xPos = 0;
	yPos = 4;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i].setup();
		grid[i].setPosition(sf::Vector2f{ xPos, yPos });

		if (xPos >= 400)
		{
			yPos += 100;
			xPos = 0;
		}
		else
		{
			xPos += 100;
		}
	}
}

void Game::clearMoves()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i].setPossibleMove(false);
	}
}

