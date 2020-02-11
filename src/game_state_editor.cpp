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
            gameView.zoom(zoomLevel);
            this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
            this->game->background.setScale(
                float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
            break;
        }
        case sf::Event::MouseMoved:
            if (this->actionState == ActionState::PANNING)
            {
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
                gameView.move(-1.0f * pos * this->zoomLevel);
                panningAnchor = sf::Mouse::getPosition(this->game->window);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                if (this->actionState != ActionState::PANNING)
                {
                    this->actionState = ActionState::PANNING;
                    this->panningAnchor = sf::Mouse::getPosition(this->game->window);
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                this->actionState = ActionState::NONE;
            }
            break;
        case sf::Event::MouseWheelMoved:
            if (event.mouseWheel.delta < 0)
            {
                gameView.zoom(2.0f);
                zoomLevel *= 2.0f;
            }
            else
            {
                gameView.zoom(0.5f);
                zoomLevel *= 0.5f;
            }
            break;
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

    this->zoomLevel = 1.0f;

    /* Centre the camera on the map */
    sf::Vector2f centre(this->map.width, this->map.height * 0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);

    this->actionState = ActionState::NONE;
}