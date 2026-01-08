#include "sand.h"
#include "grid.h"
#include <SDL2/SDL.h>

#define SAND_COLOR 0x8f6e21

void removeGrainFromArray(GrainList* list, int index)
{
    for (int i = index; i < list->count - 1; i++)
    {
        list->items[i].rect = list->items[i + 1].rect;
    }
    list->count--;
}

int grain_list_init(GrainList* g, int cap)
{
    g->items = malloc(sizeof(Grain) * cap);
    if (!g->items)
        return 0;
    g->count = 0;
    g->capacity = cap;

    return 1;
}

int sand_grains_init(SandGrains* grains, int max_grains)
{
    if (!grain_list_init(&grains->falling, max_grains))
        return 0;

    if (!grain_list_init(&grains->stationary, max_grains))
        return 0;

    return 1;
}

void grain_list_free(GrainList* list)
{
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

void sand_grains_free(SandGrains* grains)
{
    grain_list_free(&grains->falling);
    grain_list_free(&grains->stationary);
}

void paintStationaryGrain(SDL_Surface* pSurface, GrainList* stationary)
{

    for (int i = 0; i < stationary->count; i++)
    {
        SDL_FillRect(pSurface, &stationary->items[i].rect, SAND_COLOR);
    }
}

void spawn_sand(SDL_MouseButtonEvent b, GrainList* falling, Cell grid[GRID_H][GRID_W])
{
    if (b.button == SDL_BUTTON_LEFT && b.y <= 400)
    {

        int randomX = (int)((double)rand() / ((double)RAND_MAX + 1) * 40) - 20;
        int randomY = (int)((double)rand() / ((double)RAND_MAX + 1) * 40) - 20;

        int x = b.x - (GRAIN_SIZE / 2) + randomX;
        int y = b.y - (GRAIN_SIZE / 2) + randomY;

        if (falling->count >= falling->capacity)
        {
            printf("Array is full\n");
            return; // Array is full
        }

        int rounded = (x / GRAIN_SIZE) * GRAIN_SIZE;
        int gx = rounded / GRAIN_SIZE; // grain x position
        int gy = y / GRAIN_SIZE;       // grain y position

        // if the grain is within the screen size and the cell is empty
        if (gx >= 0 && gx < GRID_W && gy >= 0 && gy < GRID_H && grid[gy][gx] == CELL_EMPTY)
        {
            // set cell type to grain
            grid[gy][gx] = CELL_GRAIN;

            // create the grain in this position
            SDL_Rect grain;
            grain.x = rounded;
            grain.y = (y / GRAIN_SIZE) * GRAIN_SIZE;
            grain.w = GRAIN_SIZE;
            grain.h = GRAIN_SIZE;

            falling->items[falling->count++].rect = grain;
        }
    }
}

void stepGrain(SDL_Surface* pSurface, GrainList* falling, GrainList* stationary,
               Cell grid[GRID_H][GRID_W])
{
    for (int i = 0; i < falling->count; i++)
    {
        int gx = falling->items[i].rect.x / GRAIN_SIZE;
        int gy = falling->items[i].rect.y / GRAIN_SIZE;

        if (gx < 0 || gx >= GRID_W || gy < 0 || gy >= GRID_H)
        {
            removeGrainFromArray(falling, i);
            i--;
            continue;
        }
        int moved = 0;

        // down
        if (gy + 1 < GRID_H && grid[gy + 1][gx] == CELL_EMPTY)
        {
            grid[gy][gx] = CELL_EMPTY;
            grid[gy + 1][gx] = CELL_GRAIN;

            falling->items[i].rect.y += GRAIN_SIZE;
            moved = 1;
        }

        // down left
        else if (gy + 1 < GRID_H && gx - 1 >= 0 && grid[gy + 1][gx - 1] == CELL_EMPTY)
        {
            grid[gy][gx] = CELL_EMPTY;
            grid[gy + 1][gx - 1] = CELL_GRAIN;

            falling->items[i].rect.y += GRAIN_SIZE;
            falling->items[i].rect.x -= GRAIN_SIZE;
            moved = 1;
        }
        
        else if (gy + 1 < GRID_H && gx + 1 < GRID_W && grid[gy + 1][gx + 1] == CELL_EMPTY)
        {
            grid[gy][gx] = CELL_EMPTY;
            grid[gy + 1][gx + 1] = CELL_GRAIN;

            falling->items[i].rect.y += GRAIN_SIZE;
            falling->items[i].rect.x += GRAIN_SIZE;
            moved = 1;
        }

        if (!moved)
        {

            if (stationary->count < stationary->capacity)
            {
                stationary->items[stationary->count++].rect = falling->items[i].rect;
            }

            removeGrainFromArray(falling, i);
            i--;
            continue;
        }

        SDL_FillRect(pSurface, &falling->items[i].rect, SAND_COLOR);
    }
}