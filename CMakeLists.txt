# Versão do CMake
cmake_minimum_required(VERSION 3.18)

# Projeto
project(CampoMinado LANGUAGES CXX)

# Versão do C++
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

find_package(SFML 2.5 COMPONENTS graphics audio main REQUIRED)

# Fontes do projeto
set(PROJECT_SOURCES 
    src/Main.cpp
    src/Components/Button.h
    src/Components/Button.cpp
    src/Core/Board.h
    src/Core/Board.cpp
    src/Core/BoardItem.h
    src/Core/BoardItem.cpp   
    src/Core/GameManager.h   
    src/Core/GameManager.cpp   
    src/Screens/Screen.h
    src/Screens/Screen.cpp
    src/Screens/TitleScreen.h
    src/Screens/TitleScreen.cpp
    src/Screens/GameScreen.h
    src/Screens/GameScreen.cpp
    src/Screens/GameOverScreen.h
    src/Screens/GameOverScreen.cpp
    src/System/AssetManager.h
    src/System/AssetManager.cpp
)

# Gerar executável
add_executable(CampoMinado ${PROJECT_SOURCES})
target_link_libraries(CampoMinado sfml-graphics sfml-audio sfml-main)