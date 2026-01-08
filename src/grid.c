#include "grid.h"
#include <stdlib.h>

Cell grid[GRID_H][GRID_W];

void grid_clear(){
    for (int y = 0; y < GRID_H; y++)
    {
        for (int x = 0; x < GRID_W; x++)
        {
            grid[y][x] = CELL_EMPTY;
        }
    }

}