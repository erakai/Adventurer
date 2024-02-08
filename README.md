# Adventurer

## Summary
Adventurer is a top down role playing game inspired by western progression fantasy, built as an exercise in learning C++ and SDL2. 

## Getting Started

**Dependencies**

- CMake, Make, G++
- SDL2, SDL Image

You will need to have SDL2 in an accessible location. On mac/linux, install it with your package manager of choice. On Windows, you should add `SDL2.dll` and `SDL2_image.dll` to `/build`. Additionally make sure that you have libpng (a submodule of SDL Image) and it's located at `C:/Program Files(x86)/libpng`. This will let cmake find it. 

**Building**
```bash
git clone ...
cd Adventurer
mkdir build
cd build
cmake ..
make
```

If you are getting weird errors with VSCode, try setting the intellisense C++ configuration provider to cmake tools.