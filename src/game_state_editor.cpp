#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "game_state_editor.hpp"

void GameStateEditor::draw(const float dt)

{
    std::cout << "Desenhando editor: " << std::endl;

    this->game->window.clear(sf::Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->backgroundGame);

    this->game->window.setView(this->gameView);
    this->map.draw(this->game->window, dt);

    return;
}

void GameStateEditor::update(const float dt)
{
    (void)dt;
    return;
}

void GameStateEditor::handleInput()
{
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
        /* Close the window */
        case sf::Event::Closed:
        {
            this->game->window.close();
            break;
        }
        /* Resize the window */
        case sf::Event::Resized:
        {
            gameView.setSize(event.size.width, event.size.height);
            guiView.setSize(event.size.width, event.size.height);
            this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
            this->game->background.setScale(
                float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
            break;
        }
        default:
            break;
        }
    }

    return;
}

GameStateEditor::GameStateEditor(Game *game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);

    map = Map(game->tileAtlas);

    /* Centre the camera on the map */
    sf::Vector2f centre(this->map.width, this->map.height*0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);
}