project (adventurer-engine)

# Source list for the engine
set(LIB_SOURCES
  src/core/game.cpp
  src/core/scene.cpp
  src/core/input.cpp
  src/core/node.cpp
  src/display/display.cpp
  src/objs/game_object.cpp
  src/objs/entity.cpp
  src/objs/collider.cpp
  src/utils/logger.cpp
  src/utils/quadtree.cpp
)

# The library
add_library(${PROJECT_NAME} ${LIB_SOURCES})

# Set include dir
target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# Link to sdl
target_include_directories(${PROJECT_NAME}
  ${ADV_SDL_INCLUDE}
)

if (WIN32 AND NOT MSVC)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${ADV_SDL_LINK_W})
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE ${ADV_SDL_LINK_M})
endif()