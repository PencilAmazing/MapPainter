#pragma once

#include "types.h"
#include "cell.h"

Cell CreateSpray()
{
    float random = (float)GetRandomValue(70, 90) / 100.f;
    Color base = GREEN;
    Color _col = Color{ (unsigned char)(random * base.r), (unsigned char)(random * base.g),(unsigned char)(random * base.b), 255 };
    int vx = (short)GetRandomValue(-5, 5);
    return Cell(CellType::Spray, _col, vx, 1);
};

void ProcessSpray(CellularData& data, CellMap& map)
{
    // Copy data
    Cell cell = map[data.x][data.y];
    // Apply motion equations
    // FIXME particles going too fast might pass through others
    // Apply line tracing collision later
    int targetx = std::clamp(data.x + cell._vx, 0, mapSize - 1);
    int targety = std::clamp(data.y + cell._vy, 0, mapSize - 1);

    if (map[targetx][targety]._id != CellType::Air) {
        targetx = data.x;
        targety = data.y;
    }
    map[data.x][data.y] = CreateAir();
    cell.flipper = !cell.flipper;
    map[targetx][targety] = cell;
};
