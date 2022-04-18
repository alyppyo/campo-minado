#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow * window, int lines, int columns, int bombs, int specialists) :
    board_(lines, columns, bombs, specialists), Screen::Screen(window) {

    // Inicializar componentes.
    buttonSpace_ = 2;
    headerHeight_ = 100;
    boardMargin_ = 8;
    boardButtons_ = std::vector(board_.lines(), std::vector<BoardSquare>(board_.columns()));
    window_ = window;
    state_ = ScreenState::Idle;
    
    buttonSize_ = sf::Vector2u(boardButtons_[0][0].size().x, boardButtons_[0][0].size().y);
    boardSize_ = sf::Vector2u(board_.columns()*(buttonSize_.x+buttonSpace_)-buttonSpace_+2*boardMargin_,
                              board_.lines()*(buttonSize_.y+buttonSpace_)-buttonSpace_+2*boardMargin_);

    resize(boardSize_.x, headerHeight_ + boardSize_.y);

    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            auto itemContent = board_.item({i,j}).content();
            if(itemContent == ItemContent::Bomb)
                boardButtons_[i][j].setContent(AssetManager::texture(Texture::Bomb));
            else
                boardButtons_[i][j].setContent(std::string(1,itemContent));

            boardButtons_[i][j].setPosition(sf::Vector2f(j*(buttonSize_.x+buttonSpace_)+boardMargin_,
                                                         headerHeight_+i*(buttonSize_.y+buttonSpace_)+boardMargin_));
        }
    }

    bombsCounterLabel_.setFont(AssetManager::font(Font::MotionControl));
    bombsCounterLabel_.setString(sf::String("Bombas: " + std::to_string(bombs)));
    bombsCounterLabel_.setCharacterSize(30);
    bombsCounterLabel_.setFillColor(sf::Color::White);
    centerAtPosition(bombsCounterLabel_, 0.0);
    bombsCounterLabel_.move(sf::Vector2f(-80,50));

    specialistsCounterLabel_.setFont(AssetManager::font(Font::MotionControl));
    specialistsCounterLabel_.setString(sf::String("Especialistas: " + std::to_string(specialists)));
    specialistsCounterLabel_.setCharacterSize(30);
    specialistsCounterLabel_.setFillColor(sf::Color::White);
    centerAtPosition(specialistsCounterLabel_, 0.0);
    specialistsCounterLabel_.move(sf::Vector2f(80,52));
}

void GameScreen::draw(sf::Vector2i mousePosition, MouseState mouseState) {
    // Acionar construtor da classe base.
    Screen::draw(mousePosition, mouseState); 

    // Desenhar cabeçalho.
    drawHeader();

    // Obter coordenadas do botão no qual o mouse está passando.
    int line = (mousePosition.y-headerHeight_-boardMargin_)/(buttonSize_.y+buttonSpace_);
    int column = (mousePosition.x-boardMargin_)/(buttonSize_.x+buttonSpace_);
 
    // Verificar se as coordenadas encontradas são válidas.
    bool squareFound = isValidCoord(line, column);

    // Caso a coordenada seja válida, definir estado da casa do tabuleiro.
    if(squareFound && boardButtons_[line][column].state() != BoardSquareState::Pressed) {
        auto& boardItem = board_.item({line,column});

        // Modificar visualização das casas de acordo com o estado do tabuleiro.
        if(mouseState == MouseState::RightButtonPressed) {
            boardButtons_[line][column].setFlagged(!boardButtons_[line][column].flagged());
            
            if(boardItem.state() == ItemState::NotSelected)
                boardItem.setState(ItemState::Flagged);
            else if(boardItem.state() == ItemState::Flagged)
                boardItem.setState(ItemState::NotSelected);
        }
        else if(mouseState == MouseState::LeftButtonPressed && !boardButtons_[line][column].flagged()) {
            boardButtons_[line][column].setState(BoardSquareState::Pressed);
            updateBoard(line, column);

            // Verificar se houve vitória ou derrota.
            if(boardItem.isBomb() && boardItem.state() != ItemState::Flagged) 
                state_ = ScreenState::ChangeToGameOverDefeat;
            else if(board_.areAllSelected())
                state_ = ScreenState::ChangeToGameOverVictory;
        }
        else if(mouseState == MouseState::MiddleButtonPressed && !boardButtons_[line][column].flagged() && board_.specialists() > 0) {
            board_.decreaseSpecialistsNumber();
            specialistsCounterLabel_.setString(sf::String("Especialistas: " + std::to_string(board_.specialists())));

            boardButtons_[line][column].setState(BoardSquareState::Pressed);
            updateBoard(line, column);

            // Verificar se houve vitória.
            if(board_.areAllSelected())
                state_ = ScreenState::ChangeToGameOverVictory;
        }
        else
            boardButtons_[line][column].setState(BoardSquareState::MouseHovering);
    }

    // Desenhar todos as casas do tabuleiro, com exceção daquela na qual o mouse está sobre.
    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            if(squareFound && i == line && j == column) continue;
            window_->draw(boardButtons_[i][j]);
        }
    }

    // Checagem realizada novamente para garantir que a casa sobrevoada pelo mouse seja desenhada.
    if(squareFound) {
        // Caso alguma casa tenha sido encontrada no passo anterior, desenhá-la.
        // Volta ao estado de ociosa para aguardar a próxima iteração.
        window_->draw(boardButtons_[line][column]);
        boardButtons_[line][column].setState(BoardSquareState::Idle);
    }
}

void GameScreen::drawHeader() {
    window_->draw(bombsCounterLabel_);
    window_->draw(specialistsCounterLabel_);
}

bool GameScreen::isValidCoord(int line, int column) {
    return line > -1 && line < board_.lines() &&
           column > -1 && column < board_.columns();
}

void GameScreen::updateBoard(int line, int column) {
    Coord itemCoord {line,column};
    board_.selectItem(itemCoord);
    
    for(int i = 0; i < board_.lines(); ++i) {
        for(int j = 0; j < board_.columns(); ++j) {
            if(boardButtons_[i][j].state() != BoardSquareState::Pressed && board_.item({i,j}).state() == ItemState::Selected)
                boardButtons_[i][j].setState(BoardSquareState::Pressed);
        }
    }   
}