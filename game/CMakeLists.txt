project (adventurer-game)

# Determine source list
set(GAME_SOURCES
   player.cpp
   main.cpp)

# The binary
add_executable(${PROJECT_NAME} ${GAME_SOURCES})

# Move one directory up for convenience
cmake_path(GET PROJECT_BINARY_DIR PARENT_PATH MOVE_TO)
if (WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${MOVE_TO}/adventurer.exe
  )
else()
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${MOVE_TO}/adventurer
  )
endif()


# Add game engine
target_link_libraries(${PROJECT_NAME} PRIVATE adventurer-engine)

# Add dependency on assets
add_dependencies(${PROJECT_NAME} assets)

# Link to sdl
target_include_directories(${PROJECT_NAME}
  ${ADV_SDL_INCLUDE}
)

if (WIN32 AND NOT MSVC)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${ADV_SDL_LINK_W})
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE ${ADV_SDL_LINK_M})
endif()