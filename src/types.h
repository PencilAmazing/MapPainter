#pragma once

#include <vector>

#define CellMap std::vector<std::vector<std::shared_ptr<Cell>>>

typedef struct CellularData {
    int x;
    int y;
} CellularData;

enum class CellType {
    Air,
    Sand,
    Static,
    END_TYPE // keep this at the end
};