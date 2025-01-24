# Adventurer

## Summary

A 2D game engine built as an exercise in learning SDL2.

## Getting Started

You will need to have SDL2 in an accessible location. On mac/linux, install it with your package manager of choice. On Windows, you should add `SDL2.dll` and `SDL2_image.dll` to `/build`. Additionally make sure that you have libpng (a submodule of SDL Image) and it's located at `C:/Program Files(x86)/libpng`. This will let cmake find it.

**Building**

```bash
git clone ...
cd Adventurer
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
./adventurer
```

## Videos

https://github.com/user-attachments/assets/04e33062-38d1-4f0d-9367-6e263b0c9537

https://github.com/user-attachments/assets/f7f5ff0b-017e-4d57-978f-6fb751746a1c

