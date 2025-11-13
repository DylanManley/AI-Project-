/// <summary>
/// author Dylan Manley
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
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


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
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
							selectedPiece->place(grid[i].getPosition());
							selectedPiece->selected = false;
							selectedPiece = nullptr;
							playerTurn = false;
							placedPieces++;
							return;
						}
					}
				}
			}
		}
		else // AI Turn
		{
			int pieceChoice = rand() % 3 + 1;
			int tileChoice = rand() % GRID_SIZE;

			while (grid[tileChoice].isOccupied())
			{
				tileChoice = rand() % GRID_SIZE;
			}

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
				grid[tileChoice].setOccupied(true);
				selectedPiece->place(grid[tileChoice].getPosition());
				selectedPiece->selected = false;
				selectedPiece = nullptr;
				playerTurn = true;
				placedPieces++;
				return;
			}
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
			/*for (int i = 0; i < GRID_SIZE; i++)
			{
				if (grid[i].isHovered(boardPos) && selectedPiece != nullptr)
				{
					grid[i].setColour(sf::Color(0, 0, 255, 120));
				}
				else if (grid[i].isHovered(boardPos) && !grid[i].isPossibleMove())
				{
					grid[i].setColour(sf::Color::White);
				}
			}*/

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (!selectedPiece)
				{
					if (snake.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &snake;
						snake.selected = true;
						snake.shape.setFillColor(sf::Color::Blue);

						for (int i = 0; i < GRID_SIZE; i++)
						{
							if (grid[i].isHovered(boardPos))
							{
								int tile = i - 1;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 4)	// Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i + 1;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 0)	// Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i - 5;
								if (tile >= 0 && tile < GRID_SIZE)	// Up
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i + 5;
								if (tile >= 0 && tile < GRID_SIZE)	// Down
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i - 6;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 4)	// Up Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i - 4;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 0)	// Up Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i + 4;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 4)	// Down Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}

								tile = i + 6;
								if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 0)	// Down Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
								}
							}
						}
						
						return;
					}
					if (frog.sprite->getGlobalBounds().contains(boardPos))
					{
						selectedPiece = &frog;
						frog.selected = true;
						frog.shape.setFillColor(sf::Color::Blue);

						for (int i = 0; i < GRID_SIZE; i++) // Highlight possible moves
						{
							if (grid[i].isHovered(boardPos))
							{
								int tile = i - 1;
								if (tile >= 0 && tile < GRID_SIZE)	// Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i - 2;	// Jump Left

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i + 1;
								if (tile >= 0 && tile < GRID_SIZE)	// Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i + 2;	// Jump Right

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i - 5;
								if (tile >= 0 && tile < GRID_SIZE)	// Up
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i - 10;	// Jump Up

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i + 5;
								if (tile >= 0 && tile < GRID_SIZE)	// Down
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i + 10;	// Jump Down

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i - 6;
								if (tile >= 0 && tile < GRID_SIZE)	// Up Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i - 12;	// Jump Up Left

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i - 4;
								if (tile >= 0 && tile < GRID_SIZE)	// Up Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i - 8;	// Jump Up Right

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i + 4;
								if (tile >= 0 && tile < GRID_SIZE)	// Down Left
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i + 8;	// Jump Down Left

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}

								tile = i + 6;
								if (tile >= 0 && tile < GRID_SIZE)	// Down Right
								{
									if (!grid[tile].isOccupied())
									{
										grid[tile].setPossibleMove(true);
										grid[tile].setColour(sf::Color(0, 0, 255, 70));
									}
									else
									{
										tile = i + 12;	// Jump Down Right

										if (tile >= 0 && tile < GRID_SIZE)
										{
											if (!grid[tile].isOccupied())
											{
												grid[tile].setPossibleMove(true);
												grid[tile].setColour(sf::Color(0, 0, 255, 70));
											}
										}
									}
								}
							}
						}

						return;
					}
					for (int i = 0; i < 3; i++)
					{
						if (donkey[i].sprite->getGlobalBounds().contains(boardPos))
						{
							selectedPiece = &donkey[i];
							donkey[i].selected = true;
							donkey[i].shape.setFillColor(sf::Color::Blue);

							for (int i = 0; i < GRID_SIZE; i++) // Highlight possible moves
							{
								if (grid[i].isHovered(boardPos))
								{
									int tile = i - 1;
									if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 4)	// Left
									{
										if (!grid[tile].isOccupied())
										{
											grid[tile].setPossibleMove(true);
											grid[tile].setColour(sf::Color(0, 0, 255, 70));
										}
									}

									tile = i + 1;
									if (tile >= 0 && tile < GRID_SIZE && tile % 5 != 0)	// Right
									{
										if (!grid[tile].isOccupied())
										{
											grid[tile].setPossibleMove(true);
											grid[tile].setColour(sf::Color(0, 0, 255, 70));
										}
									}

									tile = i - 5;
									if (tile >= 0 && tile < GRID_SIZE)	// Up
									{
										if (!grid[tile].isOccupied())
										{
											grid[tile].setPossibleMove(true);
											grid[tile].setColour(sf::Color(0, 0, 255, 70));
										}
									}

									tile = i + 5;
									if (tile >= 0 && tile < GRID_SIZE)	// Down
									{
										if (!grid[tile].isOccupied())
										{
											grid[tile].setPossibleMove(true);
											grid[tile].setColour(sf::Color(0, 0, 255, 70));
										}
									}
								}
							}

							return;
						}
					}
				}
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

	m_window.display();
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

	snake.setUp(snakeTex, sf::Vector2f{ 10, yPos });
	frog.setUp(frogTex, sf::Vector2f{ 110, yPos });
	for (int i = 0; i < 3; i++)
	{
		donkey[i].setUp(donkeyTex, sf::Vector2f{xPos, yPos});
		xPos += 100;
	}

	xPos = -10000;
	yPos = -10000;

	aiSnake.setUp(snakeTex, sf::Vector2f{ 10, yPos });
	aiFrog.setUp(frogTex, sf::Vector2f{ 110, yPos });
	for (int i = 0; i < 3; i++)
	{
		aiDonkey[i].setUp(donkeyTex, sf::Vector2f{ xPos, yPos });
		xPos += 100;
	}
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
