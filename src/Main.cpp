#include "Main.hpp"
#include "game.hpp"
#include "game_state_start.hpp"
using namespace std;
int main()
{
	Game game;

	game.pushState(new GameStateStart(&game));
	game.gameLoop();

	return 0;
}
