#include "GameManager.h"

GameManager::GameManager() : 
    screenWidth_(600), screenHeight_(800),
    window_(sf::VideoMode(screenWidth_, screenHeight_), "Campo Minado", sf::Style::Titlebar | sf::Style::Close),
    lines_(15), columns_(15), bombs_(20), specialists_(1) {
    // Iniciar o gerenciador de assets.
    AssetManager::loadAssets();
}

GameManager::~GameManager() {}

void GameManager::checkScreenStatus() {
    if(currentScreen_->state() == ScreenState::ChangeToTitle) {
        currentScreen_->resize(screenWidth_, screenHeight_);
        currentScreen_ = std::make_unique<TitleScreen>(&window_);
    }
    else if(currentScreen_->state() == ScreenState::ChangeToOptions) {
        currentScreen_ = std::make_unique<OptionsScreen>(&window_, lines_, columns_, bombs_, specialists_);
    }
    else if(currentScreen_->state() == ScreenState::ChangeToGame) {
        currentScreen_ = std::make_unique<GameScreen>(&window_, lines_, columns_, bombs_, specialists_);
    }
    else if(currentScreen_->state() == ScreenState::ChangeToGameOverVictory ||
            currentScreen_->state() == ScreenState::ChangeToGameOverDefeat) {
        currentScreen_->resize(screenHeight_, screenWidth_);
        currentScreen_ = std::make_unique<GameOverScreen>(&window_, currentScreen_->state() == ScreenState::ChangeToGameOverVictory);
    }
}

void GameManager::loop() {
    sf::Vector2i mousePosition;

    // Laço principal do jogo.
    while (window_.isOpen()) {
        MouseState mouseState = MouseState::Idle;

        // Verificar se o estado da tela atual mudou.
        checkScreenStatus();
        
        // Verificar eventos gerados.
        sf::Event event;

        while (window_.pollEvent(event)) {
            // Tratar eventos de mouse.
            if(event.type == sf::Event::MouseMoved) 
                mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            else if(event.type == sf::Event::MouseLeft)
                mousePosition = sf::Vector2i(-1,-1);
            
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left)
                    mouseState = MouseState::LeftButtonPressed;
                else if(event.mouseButton.button == sf::Mouse::Right)
                    mouseState = MouseState::RightButtonPressed;
                else if(event.mouseButton.button == sf::Mouse::Middle)
                    mouseState = MouseState::MiddleButtonPressed;
            }

            // Fechar a janela caso o botão seja acionado.
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        // Desenhar tela atual.
        currentScreen_->draw(mousePosition, mouseState);

        // Mostrar novo frame.
        window_.display();
    }
}

void GameManager::start() {
    // Criar novo jogo e iniciar seus componentes.    
    currentScreen_ = std::make_unique<TitleScreen>(&window_);

    // Iniciar o laço principal do jogo.
    loop();
}
