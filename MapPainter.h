#pragma once

#include <iostream>
#include <assert.h>
#include <string>

#include "src/types.h"

#include "src/cell.h"
#include "src/sand.h"
#include "src/static.h"

std::shared_ptr<Cell> MakeCell(CellType type)
{
    switch (type) {
    case CellType::Air:
        return std::make_shared<Cell>();
        break;
    case CellType::Sand:
        return std::make_shared<Sand>();
        break;
    case CellType::Static:
        return std::make_shared<Static>();
        break;
    case CellType::END_TYPE:
        assert(false); // not cool
        return std::make_shared<Cell>();
        break;
    default:
        break;
    }
}

CellType QuerySelectedType(int key)
{
    switch (key) {
    case 0:
        break;
    case KEY_ZERO:
        return CellType::Air;
        break;
    case KEY_ONE:
        return CellType::Sand;
        break;
    case KEY_TWO:
        return CellType::Static;
        break;
    default:
        return CellType::Air;
        break;
    }
}

void ProcessMap(CellMap& map, const CellMap& prevGeneration)
{
    int mapSize = map.size();
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            std::shared_ptr<Cell> cell = prevGeneration[i][j];
            //const CellType type = cell->id();
            CellularData data = { i,j };
            cell->ProcessCell(data, map, prevGeneration);
        }
    }
};
