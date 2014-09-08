#pragma once

#include "GameEngine.h"

class IGameState
{
public:
  virtual void Init() = 0;
  virtual void Cleanup() = 0;

  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual void Draw() = 0;
  virtual void Keyboard(unsigned char, int, int) = 0;
  virtual void SpecialFunc(int, int, int) = 0;
};

