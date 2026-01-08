#ifndef SAND_H
#define SAND_H
#include "grid.h"
#include <SDL2/SDL.h>

// Forward declarations / shared types
// (These must match the definitions in sand.c / grid.h)
typedef struct
{
    SDL_Rect rect;
    int fall_speed;
} Grain;

typedef struct
{
    Grain* items;
    int count;
    int capacity;
} GrainList;

typedef struct
{
    GrainList falling;
    GrainList stationary;
} SandGrains;

// Public sand API
void removeGrainFromArray(GrainList* list, int index);

int grain_list_init(GrainList* g, int cap);

int sand_grains_init(SandGrains* grains, int max_grains);

void grain_list_free(GrainList* list);

void sand_grains_free(SandGrains* grains);
void paintStationaryGrain(SDL_Surface* pSurface, GrainList* stationary);

void spawn_sand(SDL_MouseButtonEvent b, GrainList* falling, Cell grid[GRID_H][GRID_W]);

void stepGrain(SDL_Surface* pSurface, GrainList* falling, GrainList* stationary,
               Cell grid[GRID_H][GRID_W]);

#endif // SAND_H