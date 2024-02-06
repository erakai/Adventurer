#pragma once

#include "updatable.hpp"

#include <string>
#include <vector>

namespace adv
{

class Scene: public Updatable
{
  public:
    Scene(std::string name) :
      title(name) {}
    
    void add_child(Updatable* u);

    void update(long delta) override;
    void render(long delta) override;

    std::string name() { return title; }

  private:
    std::string title;
    std::vector<Updatable*> children;

};

};