#pragma once

#include "SDL_render.h"
#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace adv
{

class Texture
{
public:
  Texture(std::string name, int w, int h);
  Texture(std::string name, int w, int h, SDL_Renderer *renderer,
          std::string fp);
  ~Texture();

  void render(SDL_Renderer *renderer, Point display_pos,
              std::string sprite = "none");

  bool load_from_file(SDL_Renderer *renderer, std::string file_path);
  void set_color(Color c);
  void resize(int new_w, int new_h);

  bool register_sprite(std::string name, SDL_Rect src_rect);

  std::string get_name();
  bool is_loaded();
  int get_width();
  int get_height();

public:
  SDL_Texture *texture;

  std::unordered_map<std::string, SDL_Rect> sprites;

  std::string name;
  bool loaded;
  int width;
  int height;
};

} // namespace adv
