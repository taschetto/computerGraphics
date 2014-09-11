#pragma once
#include "IDrawable.h"
#include "Nacho.h"

class GlDarkness : public IDrawable
{
public:
  GlDarkness(Nacho*, float, float, float, float);
  virtual ~GlDarkness();

  Nacho* nacho;

  float left, right, bottom, top;

public:
  void Scale();
  void Translate();
  void Draw();
};
