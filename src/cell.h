#pragma once

#include "raylib.h"
#include "raymath.h"

#include "types.h"

// Should be a data only class
class Cell {
    // Everything is public because i trust you all fellas
    // Assume SI units unless otherwise
public:
    CellType _id;
    Color _col;
    unsigned short int _mass;
    short _vx, _vy;

    Cell(CellType type = CellType::Air, Color color = SKYBLUE, unsigned short mass = 0, short vx = 0, short vy = 0)
        : _id(type), _col(color), _mass(mass), _vx(vx), _vy(vy)
    {
    };

    void ApplyImpulse(Vector2 impulse)
    {
        if (_mass <= 0) return;
        _vx = (impulse.x + _mass * _vx) / _mass;
        _vy = (impulse.y + _mass * _vy) / _mass;
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