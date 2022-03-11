#pragma once

#include "raylib.h"
#include "raymath.h"

#include "types.h"

// Each cell could hold state about pixel

class Cell {
protected:
    CellType _id;
    Color _col;
    Vector2 _velocity;
    int _mass; // In grams
    Cell(CellType type, Color color, Vector2 Velocity = Vector2Zero())
    {
        _id = type;
        _col = color;
        _velocity = Velocity;
    };
public:
    Cell() : _id(CellType::Air), _col(SKYBLUE) {};
    CellType id() const { return _id; };
    Color col() const { return _col; };
    Vector2 velocity() const { return _velocity; };

    void ApplyImpulse(Vector2 impulse)
    {
        _velocity.x = (impulse.x + _mass * _velocity.x) / _mass;
        _velocity.y = (impulse.y + _mass * _velocity.y) / _mass;
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
