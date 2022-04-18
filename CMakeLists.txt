# Versão do CMake
cmake_minimum_required(VERSION 3.18)

# Projeto
project(CampoMinado LANGUAGES CXX)

# Versão do C++
set(CMAKE_CXX_STANDARD 17)

# Código-fonte do projeto
set(PROJECT_SOURCES 
    src/CampoMinado.h
    src/CampoMinado.cpp
    src/Main.cpp
    src/Tabuleiro.h
    src/Tabuleiro.cpp
    src/TabuleiroItem.h
    src/TabuleiroItem.cpp   
)

# Gerar executável
add_executable(CampoMinado ${PROJECT_SOURCES})