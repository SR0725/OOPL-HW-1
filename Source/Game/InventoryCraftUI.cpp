#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "InventoryCraftUI.h"
#include <string>
#include "../Library/tool.h"

using namespace game_framework;

InventoryCraftUI::InventoryCraftUI(bool isTable, string id, int number, string costId, int cost)
{
  this->isTable = isTable;
  this->id = id;
  this->costId = costId;
  this->cost = cost;
  this->number = number;
}

void InventoryCraftUI::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
  if (keyFind(pressedKeys, "E"))
  {
    bagOpen = true;
  }
  else
  {
    bagOpen = false;
  }
}

void InventoryCraftUI::Render(GameObject *mainObject)
{
  if (!isTable && !bagOpen)
  {
    return;
  }
  if (isTable && !craftOpen)
  {
    return;
  }

  GameObject::Render(mainObject);
  if (id == "craft_table")
  {
    bitmap.SetFrameIndexOfBitmap(0);
  }
  bitmap.ShowBitmap();
}
