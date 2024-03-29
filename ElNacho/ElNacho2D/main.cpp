#include <iostream>
#include "OpenGL.h"
#include "GameEngine.h"
#include "InitialState.h"

namespace
{
  const int ScreenWidth = 1024;
  const int ScreenHeight = 725;
  const int ScreenFps = 60;
  const char* WindowTitle = "El Nacho: a game by Guilherme Taschetto";

  void doDisplay(void);
  void doKeyboard(unsigned char, int, int);
  void doSpecialFunc(int, int, int);
  void doResize(int, int);
  void runMainLoop(int);


  GameEngine engine;
}

int main(int argc, char** argv)
{
  engine.Init(argc, argv, ::ScreenWidth, ::ScreenHeight, ::WindowTitle);

  if (!engine.InitGL())
  {
    std::cerr << "ElNacho error: Unable to initialize graphics library!" << std::endl;
    return 1;
  }

  engine.ChangeState(InitialState::Instance());

  ::glutDisplayFunc(::doDisplay);
  ::glutKeyboardFunc(::doKeyboard);
  ::glutSpecialFunc(::doSpecialFunc);
  ::glutTimerFunc(1000 / ScreenFps, ::runMainLoop, 0);
  ::glutMainLoop();

  return 0;
}

void ::runMainLoop(int ms)
{
  glutPostRedisplay();
  ::glutTimerFunc(ms, ::runMainLoop, ms);
}

void ::doDisplay(void)
{
  engine.Draw();
}

void ::doKeyboard(unsigned char key, int x, int y)
{
  engine.Keyboard(key, x, y);
}

void ::doSpecialFunc(int key, int x, int y)
{
  engine.SpecialFunc(key, x, y);
}