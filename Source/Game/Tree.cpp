#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
#include "Tree.h"
#include <string>
#include "../Library/tool.h"
#include "Item.h"

using namespace game_framework;

Tree::Tree()
{
  hp = 10;
  onAttackedTick = 0;
  centerX = -9999;
  centerY = -9999;
}

void Tree::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
  if (hp <= 0)
  {
    for (int i = 0; i < 4; i++)
    {
      Item *item = new Item();
      item->Init({"resources/log.bmp"}, this->GetX() + random(-16.0f, 16.0f), this->GetY() + random(-16.0f, 16.0f), 1.0f);
      item->SetTrigger(true);
      item->SetId("log");
      item->SetActive(true);
      gameObjects.push_back(item);
    }

    this->Destroy(gameObjects);
    return;
  }

  if (onAttackedTick > 0)
  {
    onAttackedTick -= 1.0f;
    this->SetX(centerX + sin(onAttackedTick) * 4.0f);
    this->SetY(centerY + sin(onAttackedTick) * 4.0f);

    if (onAttackedTick <= 0)
    {
      this->SetX(centerX);
      this->SetY(centerY);
    }
  }
}

void Tree::OnAttacked(GameObject *gameObject)
{
  if (onAttackedTick <= 0)
  {
    hp -= 5;
    onAttackedTick = 60.0f; // 1 second
    centerX = this->GetX();
    centerY = this->GetY();
  }
}
