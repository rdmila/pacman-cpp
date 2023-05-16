#include "../../include/model/loader.h"
#include <fstream>
#include <string>
#include "config.h"

void Loader::Load(Map& map) {
    std::ifstream map_file(MAP_FILE_PATH);
    std::string line;
    std::getline(map_file, line);
    int height = std::stoi(line);

    std::getline(map_file, line);
    int width = line.length();

    map.SetSize(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            bool is_passage = (line[j] == '0');
            map.SetCell(i, j, is_passage);
        }
        std::getline(map_file, line);
    }
}
