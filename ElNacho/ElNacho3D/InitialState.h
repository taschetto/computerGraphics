#pragma once

#include "GameState.h"

class InitialState : public GameState
{
public:
  void Init();
  void Cleanup();

  void Pause();
  void Resume();

  void HandleEvents(GameEngine*);
  void Draw();
  void Keyboard(GameEngine*, unsigned char, int, int);
  void SpecialFunc(GameEngine*, int, int, int);
  void ReshapeFunc(GameEngine*, GLsizei, GLsizei);
  void MotionFunc(GameEngine*, int, int);
  void MouseFunc(GameEngine*, int, int, int, int);

  static InitialState* Instance()
  {
    if (instance == nullptr)
      instance = new InitialState();

    return instance;
  }

private:
  InitialState() {}

  static InitialState* instance;
};

