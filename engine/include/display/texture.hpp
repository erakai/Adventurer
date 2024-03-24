#pragma once

#include "SDL_render.h"
#include "utils/color.hpp"
#include "utils/rect.hpp"

#include <string>
#include <unordered_map>

namespace adv
{

class Texture
{
public:
  Texture() {}
  Texture(SDL_Renderer *renderer, std::string fp);

  void close();

  void render(SDL_Renderer *renderer, Rect display_rect,
              std::string sprite = "none");
  void render(SDL_Renderer *renderer, Rect display_rect, SDL_Rect clip);

  bool load_from_file(SDL_Renderer *renderer, std::string file_path);

  void set_color(Color c);
  void reset_color();

  bool register_sprite(std::string name, SDL_Rect src_rect);

  bool is_loaded();
  std::string get_filepath();
  SDL_Texture *get_texture();

public:
  SDL_Texture *texture = nullptr;

  std::unordered_map<std::string, SDL_Rect> sprites;

  std::string filepath;
  bool loaded = false;
};

} // namespace adv
