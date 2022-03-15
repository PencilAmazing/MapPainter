#pragma once

#include "raylib.h"
#include "raymath.h"

#include "types.h"

// Should be a data only class
class Cell {
public:
    // Everything is public because i trust you all fellas
    CellType _id;
    Color _col;
    int _vx, _vy;
    bool flipper;

    Cell(CellType type = CellType::Air, Color color = SKYBLUE, short vx = 0, short vy = 0)
        : _id(type), _col(color), _vx(vx), _vy(vy), flipper(false)
    {
    };

    static const int SIZE = 5;

    static int RoundToNearestSize(int pos)
    {
        //if (pos < 0) pos = 0; // Limit
        return round(pos / SIZE) * SIZE;
    }

    static Vector2 RoundToNearestSize(int x, int y, int padding = 0)
    {
        Vector2 result = Vector2{ 0,0 };
        int correctedx = round(x - padding * (x / SIZE));
        int correctedy = round(y - padding * (y / SIZE));
        result.x = RoundToNearestSize(correctedx);
        result.y = RoundToNearestSize(correctedy);
        return result;
    };

    static Vector2 RoundToNearestSize(Vector2 pos, int padding = 0)
    {
        return RoundToNearestSize(pos.x, pos.y, padding);
    };

    virtual void ProcessCell(CellularData& data, CellMap& map, const CellMap& prevGeneration) { return; };

};

Cell CreateAir()
{
    return Cell();
};

void ProcessAir(CellularData&, CellMap&)
{
    return;
}
