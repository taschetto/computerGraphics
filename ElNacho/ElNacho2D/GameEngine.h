#pragma once

#include <vector>

#define TEX_SPLASH 1
#define TEX_BEGIN 2
#define TEX_TARGET 3
#define TEX_BATTERY 4

class GameState;

class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void Init(int, char**, const size_t, const size_t, const char*);
  bool InitGL();
  void Cleanup();

  void ChangeState(GameState* state);
  void PushState(GameState* state);
  void PopState();

  void Draw();
  void Keyboard(unsigned char, int, int);
  void SpecialFunc(int, int, int);

private:
  std::vector<GameState*> states;
};

