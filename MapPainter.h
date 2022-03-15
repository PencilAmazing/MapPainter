﻿#pragma once

#include <iostream>
#include <assert.h>
#include <string>

#include "src/types.h"

#include "src/cell.h"
#include "src/sand.h"
#include "src/static.h"
#include "src/spray.h"
#include "src/moose.h"

const std::vector<std::string> adjectives = {
    "untidy",
    "damaging",
    "disgusting",
    "nonstop",
    "panoramic",
    "fretful",
    "left",
    "ablaze",
    "educated",
    "animated",
    "jittery",
    "serious",
    "elite",
    "actually",
    "soft",
    "neat",
    "tested",
    "aboriginal",
    "splendid",
    "little"
};

typedef struct OperationPair {
    Cell(*Create)();
    void (*Process)(CellularData&, CellMap&);
} OperationPair;

struct OperationPair Operations[] = {
    OperationPair {CreateAir, ProcessAir}, // Air
    OperationPair {CreateSand, ProcessSand}, // Sand
    OperationPair {CreateStatic, ProcessStatic}, // Static
    OperationPair {CreateSpray, ProcessSpray}, // Spray
    OperationPair {CreateMoose, ProcessMoose} // Moose
};

Cell MakeCell(CellType type)
{
    if (type >= CellType::END_TYPE) return Operations[(int)CellType::Air].Create();
    return Operations[(int)type].Create();
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

void ProcessCell(const Cell& cell, CellularData& data, CellMap& map)
{
    CellType type = cell._id;
    if (type >= CellType::END_TYPE) return Operations[(int)CellType::Air].Process(data, map);
    Operations[(int)type].Process(data, map);
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
