cmake_minimum_required(VERSION 3.1)
project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/include/")
set(CONTENT_DIR "${PROJECT_SOURCE_DIR}/content/")
set(MAP_FILE_PATH "${CONTENT_DIR}/map.txt")

find_package(Boost 1.67.0 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(SOURCES
        src/main.cpp
        src/game.cpp
        src/model/mobs.cpp
        src/model/map.cpp
        src/model/utils.cpp
        src/model/dir_choosers.cpp
        src/model/model.cpp
        src/view+controller/view.cpp
        src/view+controller/controller.cpp)

add_executable(Pacman ${SOURCES})

target_include_directories(Pacman
        PRIVATE
        ${HEADERS_DIR})

configure_file("${HEADERS_DIR}/config.h.in" "${HEADERS_DIR}/config.h")

target_link_libraries(Pacman sfml-graphics)
