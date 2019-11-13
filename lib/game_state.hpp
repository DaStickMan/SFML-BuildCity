#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "game.hpp"

#endif /* GAME_STATE_HPP */

class GameState
{
public:
	Game *game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void draw() = 0;
};