#pragma once

//#include "cell.h"
#include "sand.h"

class Static : public Cell{
public:
    Static()
        : Cell(CellType::Static, BLACK)
    {
        unsigned char random = (unsigned char)GetRandomValue(0, 225);
        //float random = (float)GetRandomValue(70, 90) / 100.f;
        //_col = Color{ (unsigned char)(random * GOLD.r), (unsigned char)(random * GOLD.g),(unsigned char)(random * (float)GOLD.b), 255 };
        _col = Color{ random, random,random, 255 };
    };

    // I don't like how I copied this
    // Maybe make it swap pointers instead of allocating new cells everytime
    // Polymorphism isn't necessary here but I'm keeping it anyways
    void ProcessCell(CellularData& data, CellMap& swapmap, const CellMap& prevGeneration) override
    {
        Vector2 target = { data.x, data.y + 1 };
        std::shared_ptr<Static> newGeneration = std::make_shared<Static>();

        if (target.y >= prevGeneration.size() || prevGeneration[target.x][target.y]->id() != CellType::Air) {
            //swapmap[data.x][data.y] = std::make_shared<Sand>();
            swapmap[data.x][data.y] = newGeneration;
        } else {
            //swapmap[target.x][target.y] = std::make_shared<Sand>();
            swapmap[target.x][target.y] = newGeneration;
        }
    }
};