#pragma once

#include "object.h"

class Start : public Object
{
public:
  Start() = default;
  virtual ~Start() = default;

  std::string GetName() override { return "Start Object"; };
};