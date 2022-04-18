#include "GameManager.h"

GameManager::GameManager() : 
    window_(sf::VideoMode(600, 800), "Campo Minado", sf::Style::Titlebar | sf::Style::Close) {
    
    // Iniciar o gerenciador de assets.
    AssetManager::loadAssets();
}

GameManager::~GameManager() {}

void GameManager::checkScreenStatus() {
    if(currentScreen_->status() == ScreenStatus::ChangeToTitle)
        currentScreen_ = std::make_unique<TitleScreen>(&window_);
    else if(currentScreen_->status() == ScreenStatus::ChangeToGame)
        currentScreen_ = std::make_unique<GameScreen>(&window_, 20, 30, 40);
    else if(currentScreen_->status() == ScreenStatus::ChangeToGameOverVictory ||
            currentScreen_->status() == ScreenStatus::ChangeToGameOverDefeat)
        currentScreen_ = std::make_unique<GameOverScreen>(&window_, currentScreen_->status() == ScreenStatus::ChangeToGameOverVictory);
}

void GameManager::loop() {
    sf::Vector2i mousePosition;

    // Laço principal do jogo.
    while (window_.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        bool mousePressed = false;

        while (window_.pollEvent(event)) {
            // Tratar eventos de mouse.
            if(event.type == sf::Event::MouseMoved) 
                mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            else if(event.type == sf::Event::MouseLeft)
                mousePosition = sf::Vector2i(-1,-1);
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                mousePressed = true;

            // Fechar a janela caso o botão seja acionado.
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        // Desenhar tela atual.
        currentScreen_->draw(mousePosition, mousePressed);

        // Mostrar novo frame.
        window_.display();

        // Verificar se o estado da tela atual mudou.
        checkScreenStatus();
    }
}

void GameManager::start() {
    // Criar novo jogo e iniciar seus componentes.    
    currentScreen_ = std::make_unique<TitleScreen>(&window_);
    // currentScreen_ = std::make_unique<GameScreen>(&window_, 20, 30, 40);
    // currentScreen_->init(&window_);
    //currentScreen_ = std::make_unique<GameOverScreen>(&window_, true);

    // Iniciar o laço principal do jogo.
    loop();
}
