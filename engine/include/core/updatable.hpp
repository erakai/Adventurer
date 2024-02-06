#pragma once

namespace adv
{

class Updatable
{
  public:
    virtual ~Updatable() {}
    virtual void update(long delta) = 0;
    virtual void render(long delta) = 0;
};

};