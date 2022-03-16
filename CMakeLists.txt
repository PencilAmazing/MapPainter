cmake_minimum_required (VERSION 3.8)

project (MapPainter C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("D:/dev/entt/src")

#link_directories("D:/dev/raylib/projects/VS2019/build/raylib/bin/x64/Release.DLL/")
add_subdirectory(libs/raylib)

# Add source to this project's executable.
add_executable (MapPainter "MapPainter.cpp" "MapPainter.h"  "src/cell.h" "src/sand.h" "src/types.h"    "src/static.h" "src/spray.h" "src/moose.h" "src/water.h")
target_link_libraries(MapPainter raylib)