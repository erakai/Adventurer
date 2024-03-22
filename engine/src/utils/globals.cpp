#include "utils/globals.hpp"

bool adv::globals::COLLISION_DEBUG = false;
bool adv::globals::PRINT_FPS_DEBUG = false;

int adv::globals::SUBPIXELS = 10;

int adv::globals::MAX_OBJECTS_PER_QUADTREE_NODE = 15;
int adv::globals::MAX_QUADTREE_LEVELS = 15;

int adv::globals::CHUNK_RENDER_DISTANCE = 5;
int adv::globals::TILES_PER_CHUNK = 64;
int adv::globals::TILE_SIZE = 16 * globals::SUBPIXELS;
