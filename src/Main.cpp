#include <cstdlib>
#include <iostream>
#include <string>

#include "Screens/GameScreen.h"
#include "System/AssetManager.h"

#include <SFML/Graphics.hpp>

int main() {
    // Criar nova janela para o jogo.
    sf::RenderWindow window(sf::VideoMode(600, 800), "Campo Minado", sf::Style::Titlebar | sf::Style::Close);
    
    // Iniciar o gerenciador de assets.
    AssetManager::loadAssets();
    
    // Criar novo jogo e iniciar seus componentes.    
    GameScreen gameScreen(20, 30, 40);
    gameScreen.initComponents(&window);

    sf::Vector2i mousePosition;
    
    // Laço principal do jogo.
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        bool mousePressed = false;

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseMoved) 
                mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            else if(event.type == sf::Event::MouseLeft)
                mousePosition = sf::Vector2i(-1,-1);
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                mousePressed = true;

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        gameScreen.draw(mousePosition, mousePressed);

        // end the current frame
        window.display();
    }

    return EXIT_SUCCESS;
}
