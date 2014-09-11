#pragma once

#include "GameState.h"

class WinState : public GameState
{
private:
  WinState() {}

  static WinState* instance;

public:
  void Init();
  void Cleanup();

  void Pause();
  void Resume();

  void HandleEvents(GameEngine*);
  void Draw();
  void Keyboard(GameEngine*, unsigned char, int, int);
  void SpecialFunc(GameEngine*, int, int, int);

  static WinState* Instance()
  {
    if (instance == nullptr)
      instance = new WinState();

    return instance;
  }
};

