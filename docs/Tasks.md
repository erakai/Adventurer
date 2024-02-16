# Tasks

- [x] make red box unable to walk through green box
- [x] fps tracker
- [x] way to have objects/nodes kill themselves
- [ ] make particle system generate many many boxes
- [ ] camera - moving, zooming in and out
- [ ] sound manager
- [ ] animation player - need to be able to tie callbacks, hitboxes, etc to anims
- [ ] ui library
- [ ] resource / texture / spritesheet loader

Possible tools?
- [ ] level designer / tile mapper
- [ ] anim editor

https://www.youtube.com/watch?v=GK0jHlv3e3w
https://github.com/scarsty/SDL2-particles/blob/master/ParticleSystem.h

https://gamedev.stackexchange.com/questions/74858/how-can-i-improve-my-collision-detections-performance

https://gamedev.stackexchange.com/questions/77701/how-to-handle-collisions-without-ugly-conditionals-and-type-checking

https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det

https://discourse.libsdl.org/t/creating-an-easily-distributable-executable-file/24413/8

eventually collision updates:
- remove vector from quadtree and have top level allocate all memory
- implement other optimizations from stack overflow post
- when moving, move the maximum distance if moving your velocity causes a collision
  - need to use colliders instead of size rect