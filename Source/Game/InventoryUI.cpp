#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
#include "InventoryUI.h"
#include "MainCharacter.h"
#include <string>
#include "../Library/tool.h"

using namespace game_framework;

void InventoryUI::SetInventory(Inventory *inventory)
{
  this->inventory = inventory;
}

void InventoryUI::showAmount()
{
}

void InventoryUI::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
}

void InventoriesUI::Init(MainCharacter *mainCharacter, vector<GameObject *> &gameObjects)
{
  GameObject::Init({"resources/empty.bmp"}, 100, 0, 0);

  this->mainCharacter = mainCharacter;
  for (int i = 0; i < 6; i++)
  {
    inventoryUI[i] = new InventoryUI();
    inventoryUI[i]->Init({"resources/empty_inventory.bmp"}, 166 + (float)i * 52, 408.0f, 0);
    inventoryUI[i]->SetUI(true);
    inventoryUI[i]->SetActive(true);
    gameObjects.push_back(inventoryUI[i]);
  }
}
void InventoriesUI::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
}
