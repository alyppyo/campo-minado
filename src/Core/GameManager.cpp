#include "GameManager.h"

GameManager::GameManager() : 
    screenWidth_(600), screenHeight_(800),
    window_(sf::VideoMode(screenWidth_, screenHeight_), "Campo Minado", sf::Style::Titlebar | sf::Style::Close) {
    
    // Iniciar o gerenciador de assets.
    AssetManager::loadAssets();
}

GameManager::~GameManager() {}

void GameManager::checkScreenStatus() {
    if(currentScreen_->status() == ScreenStatus::ChangeToTitle) {
        currentScreen_->resize(screenWidth_, screenHeight_);
        currentScreen_ = std::make_unique<TitleScreen>(&window_);
    }
    else if(currentScreen_->status() == ScreenStatus::ChangeToGame)
        currentScreen_ = std::make_unique<GameScreen>(&window_, 20, 30, 40);
    else if(currentScreen_->status() == ScreenStatus::ChangeToGameOverVictory ||
            currentScreen_->status() == ScreenStatus::ChangeToGameOverDefeat) {
        currentScreen_ = std::make_unique<GameOverScreen>(&window_, currentScreen_->status() == ScreenStatus::ChangeToGameOverVictory);
    }
}

void GameManager::loop() {
    sf::Vector2i mousePosition;

    // Laço principal do jogo.
    while (window_.isOpen()) {
        bool mousePressed = false;

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
            
            mousePressed = (event.type == sf::Event::MouseButtonPressed &&
                            event.mouseButton.button == sf::Mouse::Left);

            // Fechar a janela caso o botão seja acionado.
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        // Desenhar tela atual.
        currentScreen_->draw(mousePosition, mousePressed);

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
