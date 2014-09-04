#include "Instancia.h"


Instancia::Instancia(void)
{

  ex = ey = 1;
  tx = ty = 0;
  angulo = 0;
}


Instancia::~Instancia(void)
{
}

float Instancia::getEx()
{
  return ex;
}
float Instancia::getEy()
{
  return ey;
}
float Instancia::getTx()
{
  return tx;
}
float Instancia::getTy()
{
  return ty;
}
float Instancia::getAngulo()
{
  return angulo;
}

void Instancia::incrementaAngulo()
{
  angulo += 1;
}
void Instancia::decrementaAngulo()
{
  angulo = angulo - 1;
}
void Instancia::decrementaEx()
{
  ex = ex - 0.1;
}
void Instancia::decrementaEy()
{
  ey = ey - 0.1;
}

void Instancia::decrementaTx()
{
  tx = tx - 0.1;
}
void Instancia::decrementaTy()
{
  ty = ty - 0.1;
}
void Instancia::incrementaEx()
{
  ex = ex + 0.1;
}
void Instancia::incrementaEy()
{
  ey = ey + 0.1;
}
void Instancia::incrementaTx()
{
  tx = tx + 0.1;
}
void Instancia::incrementaTy()
{
  ty = ty + 0.1;
}
