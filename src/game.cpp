#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"
#include "animation_handler.hpp"

void Game::pushState(GameState *state)
{
	this->states.push(state);
	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState *state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState *Game::peekState()
{
	if (this->states.empty())
		return nullptr;
	return this->states.top();
}

void Game::gameLoop()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
			continue;

		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear();
		peekState()->draw(dt);
		this->window.display();
	}
}

void Game::loadTextures()
{
	texmgr.loadTexture("grass", "media/grass.png");
	texmgr.loadTexture("forest", "media/forest.png");
	texmgr.loadTexture("water", "media/water.png");
	texmgr.loadTexture("residential", "media/residential.png");
	texmgr.loadTexture("commercial", "media/commercial.png");
	texmgr.loadTexture("industrial", "media/industrial.png");
	texmgr.loadTexture("road", "media/road.png");

	texmgr.loadTexture("background", "media/background.jpg");
	texmgr.loadTexture("backgroundGame", "media/backgroundGame.png");
}

void Game::loadTiles()
{
	Animation staticAnim(0, 0, 1.0f);
	this->tileAtlas["grass"] = Tile(this->tileSize,
									1,
									texmgr.getRef("grass"),
									{staticAnim},
									TileType::GRASS, 50, 0, 1);

	this->tileAtlas["forest"] = Tile(this->tileSize,
									 1,
									 texmgr.getRef("forest"),
									 {staticAnim},
									 TileType::FOREST, 100, 0, 1);

	this->tileAtlas["water"] = Tile(this->tileSize, 2, texmgr.getRef("water"),
									{Animation(0, 3, 0.5f),
									 Animation(0, 3, 0.5f),
									 Animation(0, 3, 0.5f)},
									TileType::WATER, 0, 0, 1);

	this->tileAtlas["residential"] = Tile(this->tileSize, 2, texmgr.getRef("residential"),
										  {staticAnim, staticAnim, staticAnim,
										   staticAnim, staticAnim, staticAnim},
										  TileType::RESIDENTIAL, 300, 50, 6);

	this->tileAtlas["commercial"] = Tile(this->tileSize, 2, texmgr.getRef("commercial"),
										 {staticAnim, staticAnim, staticAnim, staticAnim},
										 TileType::COMERCIAL, 300, 50, 4);

	this->tileAtlas["industrial"] = Tile(this->tileSize, 2, texmgr.getRef("industrial"),
										 {staticAnim, staticAnim, staticAnim, staticAnim},
										 TileType::INDUSTRIAL, 300, 50, 4);

	this->tileAtlas["road"] = Tile(this->tileSize, 1, texmgr.getRef("road"),
								   {staticAnim, staticAnim, staticAnim,
									staticAnim, staticAnim, staticAnim,
									staticAnim, staticAnim, staticAnim,
									staticAnim, staticAnim},
								   TileType::ROAD, 100, 0, 1);

	return;
}

Game::Game()
{
	this->loadTextures();
	this->loadTiles();

	this->window.create(sf::VideoMode(800, 600), "City Builder");
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->texmgr.getRef("background"));
	this->backgroundGame.setTexture(this->texmgr.getRef("backgroundGame"));
}

Game::~Game()
{
	while (!this->states.empty())
		popState();
}