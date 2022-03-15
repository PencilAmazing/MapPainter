// MapPainter.cpp : Defines the entry point for the application.
//

#include "raylib.h"
#include "raymath.h"
#include "MapPainter.h"

/*
* TODO: Polymorphism is stupid replace it with a CellType->function pointer thing
* Since that's what a vtable is anyways and make_shared looks funny here
* Make a particle selector
* gas ??!!?/1!
* brush variation
* integrate rgui or something I'm not writing raw opengl
*/

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 600;
    const int screenHeight = 650;

    CellType selectedType = CellType::Sand;

    static_assert(mapSize % 2 == 0); // why not

    CellMap workMap;
    workMap.resize(mapSize, std::vector<Cell>(mapSize, Cell()));
    CellMap renderMap;
    renderMap.resize(mapSize, std::vector<Cell>(mapSize, Cell()));

    std::string title = std::string("Falling sand but ");
    title.append(adjectives[GetRandomValue(0, adjectives.size() - 1)]);

    InitWindow(screenWidth, screenHeight, title.c_str());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        ProcessMap(workMap, renderMap);
        //workMap.swap(renderMap);
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++) {
                //renderMap[i][j].reset();
                renderMap[i][j] = workMap[i][j];
                workMap[i][j] = Cell();
            }
        BeginDrawing();

        ClearBackground(RAYWHITE);
        Vector2 mousepos = GetMousePosition();

        for (int i = 0; i < mapSize; i++) {
            for (int j = 0; j < mapSize; j++) {
                Cell& cell = renderMap[i][j];
                int x = (i * Cell::SIZE);
                int y = (j * Cell::SIZE);
                Color col = cell._col;
                //if (selected.x == x && selected.y == y)
                    //col = GOLD;
                DrawRectangle(x + padding * i, y + padding * j, Cell::SIZE, Cell::SIZE, col);
            }
        }

        std::string debug("Mouse location at: ");
        debug += std::to_string(mousepos.x);
        debug += ' ';
        debug += std::to_string(mousepos.y);
        DrawText(debug.c_str(), 10, screenHeight - 30, 12, BLACK);

        debug = "Rounded to: ";
        debug += std::to_string(Cell::RoundToNearestSize(mousepos).x);
        debug += ' ';
        debug += std::to_string(Cell::RoundToNearestSize(mousepos).y);
        DrawText(debug.c_str(), 10, screenHeight - 50, 12, BLACK);

        EndDrawing();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 selected = Cell::RoundToNearestSize(mousepos, padding);
            selected.x = fmaxf(0, selected.x);
            selected.y = fmaxf(0, selected.y);
            if (selected.x < mapSize * Cell::SIZE && selected.y < mapSize * Cell::SIZE) {
                Cell& cell = renderMap[(int)selected.x / Cell::SIZE][(int)selected.y / Cell::SIZE];
                cell = MakeCell(selectedType);
            }
        }

        int key = GetKeyPressed();
        if (key != 0) {
            selectedType = QuerySelectedType(key);
        }
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
