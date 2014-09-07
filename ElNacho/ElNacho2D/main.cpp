#include <iostream>
#include "OpenGL.h"
#include "Controller.h"

namespace
{
  const int ScreenWidth = 1000;
  const int ScreenHeight = 500;
  const char* WindowTitle = "El Nacho: a game by Guilherme Taschetto";

  void doDisplay(void);
  void doKeyboard(unsigned char, int, int);
  void doSpecialFunc(int, int, int);

  Controller* controller = nullptr;
}

int main(int argc, char* args[])
{
  ::glutInit(&argc, args);
  ::glutInitContextVersion(3, 1);

  ::glutInitDisplayMode(GLUT_DOUBLE);
  ::glutInitWindowSize(::ScreenWidth, ::ScreenHeight);
  ::glutCreateWindow(::WindowTitle);

  controller = new(std::nothrow) Controller();
  if (controller == nullptr)
  {
    std::cerr << "ElNacho error: Out of memory!" << std::endl;
    return 1;
  }

  if (!controller->InitGL())
  {
    std::cerr << "ElNacho error: Unable to initialize graphics library!" << std::endl;
    return 1;
  }

  ::glutDisplayFunc(::doDisplay);
  ::glutKeyboardFunc(::doKeyboard);
  ::glutSpecialFunc(::doSpecialFunc);
  ::glutMainLoop();

  return 0;
}

void ::doDisplay(void)
{
  controller->Display();
}

void ::doKeyboard(unsigned char key, int x, int y)
{
  controller->Keyboard(key, x, y);
}

void ::doSpecialFunc(int key, int x, int y)
{
  controller->SpecialFunc(key, x, y);
}