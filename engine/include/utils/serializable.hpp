#pragma once

#include <string>

namespace adv 
{

class Serializable
{
public:
  virtual ~Serializable() {}

  virtual void read(std::string filepath) = 0;
  virtual void write(std::string filepath) = 0;

};

}