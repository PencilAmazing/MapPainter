#pragma once

#include "types.h"
#include "cell.h"

// Utility function to create sand particles
Cell CreateSand()
{
    float random = (float)GetRandomValue(70, 90) / 100.f;
    Color _col = Color{ (unsigned char)(random * GOLD.r), (unsigned char)(random * GOLD.g),(unsigned char)(random * (float)GOLD.b), 255 };
    int vx = (short)GetRandomValue(-1, 1);
    return Cell(CellType::Sand, _col, vx, 1);
};

// Writes data to new generation
void ProcessSand(CellularData& data, CellMap& output, const CellMap& prevGeneration)
{
    // Copy data
    Cell cell = prevGeneration[data.x][data.y];
    // Apply motion equations
    // FIXME particles going too fast might pass through others
    // Apply line tracing collision later
    int targetx = std::clamp(data.x + cell._vx, 0, mapSize - 1);
    int targety = std::clamp(data.y + cell._vy, 0, mapSize - 1);

    //if (target.y >= prevGeneration.size() || prevGeneration[target.x][target.y]._id != CellType::Air) {
    if (prevGeneration[targetx][targety]._id != CellType::Air) {
        // Collision
        targetx = data.x;
        targety = data.y;
        // FIXME momentum where
        cell._vx *= GetRandomValue(-1, 1);
    }
    cell._vx *= GetRandomValue(-1, 1);
    output[targetx][targety] = cell;
};
