cmake_minimum_required(VERSION 3.1)
project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost 1.67.0 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories(model)
include_directories(view)

set(SOURCES
        main.cpp
        game.cpp
        model/loader.cpp
        model/mobs.cpp
        model/map.cpp
        model/utils.cpp
        model/dir_choosers.cpp
        model/model.cpp
        view/view.cpp controller/controller.cpp)

add_executable(Pacman ${SOURCES})

target_link_libraries(Pacman sfml-graphics)
