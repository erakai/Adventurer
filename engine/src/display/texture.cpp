#include "display/texture.hpp"
#include "SDL_image.h"
#include "SDL_render.h"
#include "utils/logger.hpp"

using namespace adv;

Texture::Texture(std::string name, int width, int height)
    : name(name), width(width), height(height)
{
}

Texture::Texture(std::string name, int width, int height,
                 SDL_Renderer *renderer, std::string fp)
    : name(name), width(width), height(height)
{
  load_from_file(renderer, fp);
}

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
  texture = nullptr;
}

void Texture::render(SDL_Renderer *renderer, Point display_pos,
                     std::string sprite)
{
  if (!is_loaded())
  {
    logger::log("Texture not loaded on render call: " + name);
    return;
  }

  SDL_Rect destination = {display_pos.x(), display_pos.y(),
                          display_pos.x() + width, display_pos.y() + height};
  if (sprite == "none")
  {
    SDL_RenderCopy(renderer, texture, nullptr, &destination);
  }
  else
  {
    SDL_RenderCopy(renderer, texture, &sprites[sprite], &destination);
  }
}

bool Texture::load_from_file(SDL_Renderer *renderer, std::string file_path)
{
  if (is_loaded())
  {
    SDL_DestroyTexture(texture);
  }

  SDL_Texture *tex = IMG_LoadTexture(renderer, file_path.c_str());
  if (tex == nullptr)
  {
    logger::log("Failed to load texture: \"" + name + "\" from \"" + file_path +
                "\"");
    return false;
  }

  loaded = true;
  return true;
}

void Texture::set_color(Color c)
{
  SDL_SetTextureColorMod(texture, c.r, c.g, c.b);
  if (c.opacity != 0xFF)
  {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, c.opacity);
  }
}

void Texture::resize(int new_w, int new_h)
{
  width = new_w;
  height = new_h;
}

bool Texture::register_sprite(std::string name, SDL_Rect src_rect)
{
  if (src_rect.x > 0 && src_rect.y > 0 && src_rect.w < width &&
      src_rect.h < height)
  {
    sprites[name] = src_rect;
    return true;
  }

  return false;
}

std::string Texture::get_name()
{
  return name;
}

bool Texture::is_loaded()
{
  return loaded;
}

int Texture::get_width()
{
  return width;
}

int Texture::get_height()
{
  return height;
}
