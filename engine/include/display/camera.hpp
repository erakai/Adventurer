#pragma once

#include "core/node.hpp"
#include "objs/game_object.hpp"
#include "utils/globals.hpp"

#include <memory>

namespace adv
{

enum class CameraType
{
  STATIC,
  CENTERED_FOLLOW,
};

class Camera : public Node
{
public:
  Camera(CameraType mode, int width, int height)
      : mode(mode), width(width * globals::SUBPIXELS),
        height(height * globals::SUBPIXELS)
  {
  }

  Rect get_viewport();
  void attach(std::shared_ptr<GameObject> attach) { attached_to = attach; }

private:
  CameraType mode;
  int width, height;

  std::shared_ptr<GameObject> attached_to;
};

} // namespace adv
