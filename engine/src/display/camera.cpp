#include "display/camera.hpp"

using namespace adv;

Rect Camera::get_viewport()
{
  switch (mode)
  {
  case CameraType::CENTERED_FOLLOW:
    if (attached_to == nullptr)
      return Rect(0, 0, width, height);
    return Rect((attached_to->pos().x() + (attached_to->size().width() / 2)) -
                    (width / 2),
                (attached_to->pos().y() + (attached_to->size().height() / 2)) -
                    (height / 2),
                (attached_to->pos().x() + (attached_to->size().width() / 2)) +
                    (width / 2),
                (attached_to->pos().y() + (attached_to->size().height() / 2)) +
                    (height / 2));
  default:
    return Rect(0, 0, width, height);
  }
}
