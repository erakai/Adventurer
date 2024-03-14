cmake_minimum_required(VERSION 3.20...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if (NOT WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

# Project definition
project(adventurer-game)

# Target to copy asset folder into binary folder
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# Locate SDL2 / SD2_Image / LIBPNG
if (NOT PNG AND WIN32 AND NOT MSVC)
    set(PNG_LIBRARY "C:/Program Files(x86)/libpng")
    set(PNG_PNG_INCLUDE_DIR "C:/Program Files(x86)/libpng/include")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Set variables for including/linking sdl
set(ADV_SDL_INCLUDE
  PUBLIC include/
  PUBLIC ${SDL2_INCLUDE_DIRS}
  PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
)

set(ADV_SDL_LINK_W
  PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32
)

set(ADV_SDL_LINK_M
  PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
)

# Create core components
add_subdirectory(external)
add_subdirectory(game)
add_subdirectory(engine)
add_subdirectory(tools)
