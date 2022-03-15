#pragma once

#include "types.h"
#include "cell.h"

// Moose coffee
Cell CreateMoose()
{
    float random = (float)GetRandomValue(70, 90) / 100.f;
    Color base = ORANGE;
    Color _col = Color{ (unsigned char)(random * base.r), (unsigned char)(random * base.g),(unsigned char)(random * base.b), 255 };
    //int vx = GetRandomValue(0, 1) ? -1 : 1;
    return Cell(CellType::Moose, _col, 1, -1);
};

void ProcessMoose(CellularData& data, CellMap& output, const CellMap& prevGeneration)
{
    // Copy data
    Cell cell = prevGeneration[data.x][data.y];
    // Apply motion equations
    // FIXME particles going too fast might pass through others
    // Apply line tracing collision later
    int targetx = std::clamp(data.x + cell._vx, 0, mapSize - 1);
    int targety = std::clamp(data.y - 1, 0, mapSize - 1);
    cell._vx *= GetRandomValue(0, 1) == 0 ? -1 : 1;

    if (prevGeneration[targetx][targety]._id != CellType::Air) {
        targetx = data.x;
        targety = data.y;
        cell._vx = GetRandomValue(-1, 1);
    }
    cell._vx = GetRandomValue(-1, 1);

    output[targetx][targety] = cell;
};
