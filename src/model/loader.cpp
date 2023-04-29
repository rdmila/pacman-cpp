#include "loader.h"
#include <fstream>
#include <iostream>
#include <string>

void Loader::Load(Map& map) {
    std::ifstream map_file("content/map.txt");
    std::string line;
    std::getline(map_file, line);
    std::cout << line << std::endl;
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
