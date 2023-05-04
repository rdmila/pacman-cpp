#include "loader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

void Loader::Load(Map& map) {
    std::ifstream map_file("../../content/map.txt"); // TODO: make better path
    std::string line;
//    std::cout << std::filesystem::current_path() << std::endl;
    std::getline(map_file, line);
    int height = std::stoi(line);

    std::getline(map_file, line);
    std::cout << line << std::endl;
    int width = line.length();
    map.SetSize(height + 2, width + 2);
    for (size_t h = 1; h <= height; ++h) {
        for (size_t w = 1; w <= width; ++w) {
            bool is_passage = (line[w] == '0');
            map.SetCell(h, w, is_passage);
        }
        std::getline(map_file, line);
    }
}
