#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateEditor : public GameState
{
private:
    sf::View gameView;
    sf::View guiView;

public:
    void draw(const float dt) override;
    void update(const float dt);
    void handleInput();

    GameStateEditor(Game *game);
};

#endif /* GAME_STATE_EDITOR_HPP */