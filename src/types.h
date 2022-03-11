#pragma once

#include <vector>
#include <algorithm>

#define CellMap std::vector<std::vector<Cell>>

const int mapSize = 100;
const int padding = 0;

typedef struct CellularData {
    int x;
    int y;
} CellularData;

enum class CellType : unsigned short int {
    Air,
    Sand,
    Static,
    Spray,
    Moose, // ???
    END_TYPE // keep this at the end
};