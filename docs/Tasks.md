# Tasks

- [x] make red box unable to walk through green box
- [x] fps tracker
- [x] way to have objects/nodes kill themselves
- [x] make particle system generate many many boxes
- [x] camera - moving, zooming in and out
- [x] resource / texture / spritesheet loader
- [ ] rewrite world system to allow for tile maps
- [ ] rewrite mouse input so drag/hold are handled
- [ ] pathfinding (https://gamedev.stackexchange.com/questions/58963/pathfinding-with-2d-non-grid-based-movement-over-uniform-terrain)
- [ ] add layers to rendering
- [ ] sound manager
- [ ] animation player - need to be able to tie callbacks, hitboxes, etc to anims
- [ ] ui library

Possible tools?

- [ ] level designer / tile mapper
- [ ] anim editor

https://www.youtube.com/watch?v=GK0jHlv3e3w
https://github.com/scarsty/SDL2-particles/blob/master/ParticleSystem.h
https://gamedev.stackexchange.com/questions/74858/how-can-i-improve-my-collision-detections-performance
https://gamedev.stackexchange.com/questions/77701/how-to-handle-collisions-without-ugly-conditionals-and-type-checking
https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det
https://discourse.libsdl.org/t/creating-an-easily-distributable-executable-file/24413/8
https://github.com/ocornut/imgui/wiki/Getting-Started#example-if-you-are-using-sdl2--openglwebgl

eventually collision updates:

- remove vector from quadtree and have top level allocate all memory
- implement other optimizations from stack overflow post
- when moving, move the maximum distance if moving your velocity causes a collision

  - need to use colliders instead of size rect

- make current scene a global variable ?
- make render() in entity call like renderself() or something if its within viewport after updating draw pos
- also make mouse_x/mouse_y generally accessible from input, give input access to camera and adjust to window as well

- bug where game object doesn't correctly collision with object in different quadtree

  - need to rewrite quadtree to be able to check a specific point, not just an object, and then get_possible_collisions(pos + velocity) instead in move()
  - low priority

- layered rendering easy: just create a map of vectors with objects in scene with layers as the key

- maybe use flood fill to optimize adding rects to stationary quadtree when tiles next to each other are both impassable