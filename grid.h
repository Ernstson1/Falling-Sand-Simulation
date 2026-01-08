#ifndef GRID_H
#define GRAIN_SIZE 10
#define GRID_W (900 / GRAIN_SIZE)
#define GRID_H (600 / GRAIN_SIZE)


typedef enum
{
    CELL_EMPTY,
    CELL_GRAIN
} Cell;

extern Cell grid[GRID_H][GRID_W];

void grid_clear();

static inline int grid_in_bounds(int gx, int gy)
{
    return gx >= 0 && gx < GRID_W && gy >= 0 && gy < GRID_H;
}

#endif // GRID_H