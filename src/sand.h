#pragma once

#include "types.h"
#include "cell.h"

class Sand : public Cell {
public:
    Sand(Color color) :
        Cell(CellType::Sand, color)
    {
    };
    Sand()
        : Cell(CellType::Sand, GOLD)
    {
        float random = (float)GetRandomValue(70, 90) / 100.f;
        _col = Color{ (unsigned char)(random * GOLD.r), (unsigned char)(random * GOLD.g),(unsigned char)(random * (float)GOLD.b), 255 };
    };

    // Writes data to new generation
    void ProcessCell(CellularData& data, CellMap& swapmap, const CellMap& prevGeneration) override
    {
        Vector2 target = { data.x, data.y + 1 };
        std::shared_ptr<Sand> newGeneration = std::make_shared<Sand>(_col);

        // If colliding
        if (target.y >= prevGeneration.size() || prevGeneration[target.x][target.y]->id() != CellType::Air) {
            swapmap[data.x][data.y] = newGeneration;
        } else {
            //swapmap[target.x][target.y] = std::make_shared<Sand>();
            swapmap[target.x][target.y] = newGeneration;
        }
    }

};