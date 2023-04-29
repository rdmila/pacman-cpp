#pragma once
#include "map.h"

class Map;

class Loader {
    // constexpr static const char* MAP_FILE = "../content/map.txt";

public:
    static void Load(Map&);
};
