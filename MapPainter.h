#pragma once

#include <iostream>
#include <assert.h>
#include <string>

#include "src/types.h"

#include "src/cell.h"
#include "src/sand.h"
#include "src/static.h"
#include "src/spray.h"
#include "src/moose.h"

Cell MakeCell(CellType type)
{
    switch (type) {
    case CellType::Air:
        return Cell();
    case CellType::Sand:
        return CreateSand();
    case CellType::Static:
        return CreateStatic();
    case CellType::Spray:
        return CreateSpray();
    case CellType::Moose:
        return CreateMoose();
    default:
        assert(false); // not cool
        return Cell();
    }
}

CellType QuerySelectedType(int key)
{
    switch (key) {
    case 0:
        break;
    case KEY_ZERO:
        return CellType::Air;
    case KEY_ONE:
        return CellType::Sand;
    case KEY_TWO:
        return CellType::Static;
    case KEY_THREE:
        return CellType::Spray;
    case KEY_FOUR:
        return CellType::Moose;
    default:
        return CellType::Air;
    }
}

// I wanted this to be a id->function hashmap
// this is why function pointers exist
void ProcessCell(const Cell& cell, CellularData& data, CellMap& map, const CellMap& prevGeneration)
{
    switch (cell._id) {
    case CellType::Air:
        break; // :)
    case CellType::Sand:
        ProcessSand(data, map, prevGeneration);
        break;
    case CellType::Static:
        ProcessStatic(data, map, prevGeneration);
        break;
    case CellType::Spray:
        ProcessSpray(data, map, prevGeneration);
        break;
    case CellType::Moose:
        ProcessMoose(data, map, prevGeneration);
        break;
    default:
        break; // :(
    }
}

void ProcessMap(CellMap& map, const CellMap& prevGeneration)
{
    int mapSize = map.size();
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            const Cell& cell = prevGeneration[i][j];
            //const CellType type = cell->id();
            CellularData data = { i,j };
            // this is stupid
            ProcessCell(cell, data, map, prevGeneration);
        }
    }
};
