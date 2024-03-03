#include "display/camera.hpp"

using namespace adv;

Rect Camera::get_viewport()
{
  switch (mode)
  {
    case CameraType::CENTERED_FOLLOW:
      if (attached_to == nullptr) return Rect(0, 0, width, height);
      return Rect(attached_to->pos().x() - (width / 2),
                  attached_to->pos().y() - (height / 2), 
                  attached_to->pos().x() + (width / 2),
                  attached_to->pos().y() + (height / 2));
    default:
      return Rect(0, 0, width, height);
  }
}