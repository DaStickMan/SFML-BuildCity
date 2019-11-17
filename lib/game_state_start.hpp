#ifndef GaME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateStart : public GameState
{
private:
	sf::View view;
	void loadgame();

public:
	void draw(const float dt);
	void update(const float dt);
	void handleInput();

	GameStateStart(Game *game);
};

#endif /* GAME_STATE_START_HPP */