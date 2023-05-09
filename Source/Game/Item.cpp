#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
#include "Item.h"
#include <string>
#include "tool.h"

using namespace game_framework;
ItemTable::ItemTable(string _id, string _path, float _rate, int _number) {
    id = _id;
    path = _path;
    rate = _rate;
    number = _number;
}


Item::Item()
{
}

void Item::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{

  if (centerX == -9999 || centerY == -9999)
  {
    centerX = this->GetX();
    centerY = this->GetY();
    tick = 0;
  }

  tick = tick + 10.0f;
  this->SetY(centerY + cos(tick / 120.0f) * 10.0f);
}

