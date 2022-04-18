/**
 * @file GameManager.cpp
 * @author Alyppyo Coutinho
 * @brief Implementação da classe que representa o gerenciador de jogo.
 * @version 0.1
 * @date 2022-04-18
 */

#include "GameManager.h"

/**
 * @brief Constrói um novo gerenciador de jogo.
 */
GameManager::GameManager() : 
    // Define as dimensões da janela.
    screenWidth_(600), screenHeight_(800),
    // Cria nova janela que será usada pelo jogo.
    window_(sf::VideoMode(screenWidth_, screenHeight_), "Campo Minado", sf::Style::Titlebar | sf::Style::Close),
    // Define os valores iniciais do tabuleiro.
    lines_(15), columns_(15), bombs_(20), specialists_(1) {
    // Iniciar o gerenciador de assets.
    AssetManager::loadAssets();
}

/**
 * @brief Destrutor padrão.
 */
GameManager::~GameManager() {}

/**
 * @brief Verifica se uma mudança de tela foi sinalizada, cria a tela correspondente e substitui a atual.
 */
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

/**
 * @brief Laço principal do jogo.
 */
void GameManager::loop() {
    // Posição do mouse.
    sf::Vector2i mousePosition;

    // Laço principal do jogo.
    while (window_.isOpen()) {
        MouseState mouseState = MouseState::Idle;

        // Verificar se o estado da tela atual mudou.
        checkScreenStatus();
        
        // Verificar eventos gerados.
        sf::Event event;

        // Processar todos os eventos na fila.
        while (window_.pollEvent(event)) {
            // Tratar eventos de mouse.
            if(event.type == sf::Event::MouseMoved) 
                mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            else if(event.type == sf::Event::MouseLeft)
                mousePosition = sf::Vector2i(-1,-1);
            
            // Verificar qual botão está sendo pressionado no momento.
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

/**
 * @brief Iniciar o jogo.
 */
void GameManager::start() {
    // Criar novo jogo e iniciar seus componentes.    
    currentScreen_ = std::make_unique<TitleScreen>(&window_);

    // Iniciar o laço principal do jogo.
    loop();
}
