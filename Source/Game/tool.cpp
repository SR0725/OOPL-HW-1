#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool keyFind(string keys, string targetKey)
{
  if (keys.find(targetKey) != string::npos)
  {
    return true;
  }
  return false;
}

float random(float bottom, float top)
{
  return (float)(rand() % (int)(top - bottom + 1) + bottom);
}