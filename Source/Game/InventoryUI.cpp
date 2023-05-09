#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "InventoryUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"

using namespace game_framework;

InventoryUI* InventoryUI::SetInventory(Inventory* inventory)
{
	this->inventory = inventory;

	return this;
}

void InventoryUI::showAmount()
{
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 12, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, (int)(x + GetWidth() - 16), (int)(y + GetHeight() - 16), std::to_string(inventory->number));
	CDDraw::ReleaseBackCDC();
}

void InventoryUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
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

void InventoryUI::Render(GameObject* mainObject)
{
	if (isBag && !bagOpen)
	{
		return;
	}

	GameObject::Render(mainObject);
	if (!inventory || inventory->number == 0)
	{
		return;
	}

	bitmap.SetFrameIndexOfBitmap(inventory->textureIndex);

	if (bagOpen)
	{
		showAmount();
	}
}

InventoryUI* InventoryUI::SetBag(bool isBag)
{
	this->isBag = isBag;

	return this;
}

InventoriesUI* InventoriesUI::Init(MainCharacter* mainCharacter, vector<GameObject*>& gameObjects)
{
	GameObject::Init({ "resources/empty.bmp" })->SetPosition(100, 0);

	this->mainCharacter = mainCharacter;
	// 快捷欄
	for (int i = 0; i < 6; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]->Init({ "resources/empty_inventory.bmp", "resources/log_inventory.bmp", "resources/craft_craft_table.bmp" })
			->SetPosition(166 + (float)i * 52, 408.0f)
			->SetUI(true)
			->SetActive(true);
		inventoryUI[i]->SetUI(true);
		inventoryUI[i]->SetActive(true);
		inventoryUI[i]->SetInventory(mainCharacter->GetInventory(i));
		inventoryUI[i]->SetBag(false);
		gameObjects.push_back(inventoryUI[i]);
	}
	// 背包
	for (int i = 6; i < 24; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]->Init({ "resources/empty_inventory.bmp", "resources/log_inventory.bmp", "resources/craft_craft_table.bmp"})
			->SetPosition(166 + (float)(i % 6) * 52, 168.0f + (float)(floor(i / 6) - 1) * 52);
		inventoryUI[i]->SetUI(true);
		inventoryUI[i]->SetActive(true);
		inventoryUI[i]->SetInventory(mainCharacter->GetInventory(i));
		inventoryUI[i]->SetBag(true);
		gameObjects.push_back(inventoryUI[i]);
	}

	return this;
}
void InventoriesUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
{
}
