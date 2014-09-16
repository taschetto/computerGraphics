#include "GameEngine.h"
#include "GameState.h"
#include "OpenGL.h"
#include "TextureManager.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init(int argc, char** argv, const size_t screenWidth, const size_t screenHeight, const char* windowTitle)
{
  ::glutInit(&argc, argv);
  ::glutInitContextVersion(3, 1);
  ::glutInitDisplayMode(GLUT_DOUBLE);
  ::glutInitWindowSize(screenWidth, screenHeight);
  ::glutCreateWindow(windowTitle);

  TextureManager::Inst()->LoadTexture("Splash.bmp", TEX_SPLASH, GL_BGR_EXT);
  TextureManager::Inst()->LoadTexture("Start.bmp", TEX_BEGIN, GL_BGR_EXT);
  TextureManager::Inst()->LoadTexture("Target.bmp", TEX_TARGET, GL_BGR_EXT);
  TextureManager::Inst()->LoadTexture("Battery.bmp", TEX_BATTERY, GL_BGR_EXT);
}

bool GameEngine::InitGL()
{
  //Initialize Projection Matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Initialize Modelview Matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  //Check for error
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
    return false;
  }

  return true;
}

void GameEngine::Cleanup()
{
  while (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }
}

void GameEngine::ChangeState(GameState* state)
{
  if (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }

  states.push_back(state);
  states.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
  if (!states.empty()) {
    states.back()->Pause();
  }

  states.push_back(state);
  states.back()->Init();
}

void GameEngine::PopState()
{
  if (!states.empty()) {
    states.back()->Cleanup();
    states.pop_back();
  }

  if (!states.empty()) {
    states.back()->Resume();
  }
}

void GameEngine::Draw()
{
  states.back()->Draw();
  states.back()->HandleEvents(this);
  
}

void GameEngine::Keyboard(unsigned char key, int x, int y)
{
  states.back()->Keyboard(this, key, x, y);
}

void GameEngine::SpecialFunc(int key, int x, int y)
{
  states.back()->SpecialFunc(this, key, x, y);
}