#pragma once

#include <vector>

class IGameState;

class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void Init(int, char**, const size_t, const size_t, const char*);
  bool InitGL();
  void Cleanup();

  void ChangeState(IGameState* state);
  void PushState(IGameState* state);
  void PopState();

  void Draw();
  void Keyboard(unsigned char, int, int);
  void SpecialFunc(int, int, int);

  //  bool Running() { return m_running; }
  //  void Quit() { m_running = false; }
  //
private:
  std::vector<IGameState*> states;

  //  bool m_running;
};

