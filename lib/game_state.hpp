#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "game.hpp"
#include <iostream>

class GameState
{
public:
	Game *game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;

	virtual ~GameState(){};
	GameState(){};
};

#endif /* GAME_STATE_HPP */
