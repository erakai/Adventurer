#pragma once

namespace adv
{

namespace globals
{
extern int FPS;

extern bool COLLISION_DEBUG;
extern bool PRINT_FPS_DEBUG;

extern int SUBPIXELS;

extern int MAX_OBJECTS_PER_QUADTREE_NODE;
extern int MAX_QUADTREE_LEVELS;

extern int CHUNK_RENDER_DISTANCE;
const int TILES_PER_CHUNK = 64;
const int TILE_SIZE = 16;

}; // namespace globals

}; // namespace adv
