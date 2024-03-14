# imgui ===================================================================
set(IMGUI_PATH "imgui")
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)
set(IMGUI_SOURCES ${IMGUI_SOURCES}
                  ${IMGUI_PATH}/backends/imgui_impl_sdl2.cpp
                  ${IMGUI_PATH}/backends/imgui_impl_sdlrenderer2.cpp
)
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH}/backends)

target_include_directories("ImGui" ${ADV_SDL_INCLUDE})
if (WIN32 AND NOT MSVC)
  target_link_libraries("ImGui" PRIVATE ${ADV_SDL_LINK_W})
else()
  target_link_libraries("ImGui" PRIVATE ${ADV_SDL_LINK_M})
endif()
