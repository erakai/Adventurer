project (tools)

# worldedit ===================================================================
set(WE_SOURCES
  worldedit/main.cpp
  worldedit/components/sidebar.cpp
  worldedit/components/tiler.cpp
  worldedit/views/editor.cpp
  worldedit/views/creator.cpp
)
add_executable(worldedit ${WE_SOURCES})

target_link_libraries(worldedit PRIVATE adventurer-engine)
target_include_directories(worldedit ${ADV_SDL_INCLUDE})
if (WIN32 AND NOT MSVC)
  target_link_libraries(worldedit PRIVATE ${ADV_SDL_LINK_W})
else()
  target_link_libraries(worldedit PRIVATE ${ADV_SDL_LINK_M})
endif()

cmake_path(GET PROJECT_BINARY_DIR PARENT_PATH MOVE_TO)
if (WIN32)
  add_custom_command(TARGET worldedit POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:worldedit> ${MOVE_TO}/worldedit.exe
  )
else()
  add_custom_command(TARGET worldedit POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:worldedit> ${MOVE_TO}/worldedit
  )
endif()
