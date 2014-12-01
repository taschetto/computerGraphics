#pragma once

#include "GameEngine.h"

class GameState
{
public:
  virtual void Init() = 0;
  virtual void Cleanup() = 0;

  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual void HandleEvents(GameEngine*) = 0;
  virtual void Draw() = 0;
  virtual void Keyboard(GameEngine*, unsigned char, int, int) = 0;
  virtual void SpecialFunc(GameEngine*, int, int, int) = 0;
  virtual void ReshapeFunc(GameEngine*, GLsizei, GLsizei) = 0;
  virtual void MotionFunc(GameEngine*, int, int) = 0;
  virtual void MouseFunc(GameEngine*, int, int, int, int) = 0;

  void ChangeState(GameEngine* engine, GameState* state)
  {
    engine->ChangeState(state);
  }
};

