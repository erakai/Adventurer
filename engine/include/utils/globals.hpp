#pragma once

namespace adv
{

namespace globals
{

const bool COLLISION_DEBUG = true;
const bool PRINT_FPS_DEBUG = false;

const int SUBPIXELS = 10;

const int MAX_OBJECTS_PER_QUADTREE_NODE = 15;
const int MAX_QUADTREE_LEVELS = 15;

const int CHUNK_RENDER_DISTANCE = 5;
const int TILES_PER_CHUNK = 64;
const int TILE_SIZE = 16 * SUBPIXELS;

}; // namespace globals

}; // namespace adv
