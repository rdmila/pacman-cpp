cmake_minimum_required(VERSION 3.1)
project(Pacman)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(model)
include_directories(view)

set(SOURCES
    main.cpp
    game.cpp
    model/mobs.cpp
    model/model.cpp
    view/view.cpp
)

add_executable(Pacman ${SOURCES})
