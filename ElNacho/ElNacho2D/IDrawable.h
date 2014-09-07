#pragma once
#include "OpenGL.h"

class IDrawable
{
public:
  virtual void Scale() = 0;
  virtual void Translate() = 0;
  virtual void Draw() = 0;

  void Render()
  {
    glPushMatrix();
    this->Scale();
    this->Translate();
    this->Draw();
    glPopMatrix();
  }
};