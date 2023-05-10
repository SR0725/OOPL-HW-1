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


Inventory* InventoryUI::GetInventory()
{
	return inventory;
}


void InventoryUI::showAmount()
{
	if (!inventory || inventory->number == 0 || inventory->id == "empty")
	{
		return;
	}
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 12, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, (int)(x + GetWidth() - 16), (int)(y + GetHeight() - 16), std::to_string(inventory->number));
	CDDraw::ReleaseBackCDC();
}

void InventoryUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, int mouseX, int mouseY)
{
	if (isDrag && bagOpen)
	{
		if (keyFind(pressedKeys, "0"))
		{
			SetX((float)mouseX - GetWidth() / 2);
			SetY((float)mouseY - GetHeight() / 2);
		}
		else {
			// 取得所有其他物品欄位 看是否有重疊
			for (unsigned int i = 0; i < gameObjects.size(); i++)
			{
				if (gameObjects[i]->GetId() != "inventory")
				{
					continue;
				}
				if (gameObjects[i] == this)
				{
					continue;
				}
				if (gameObjects[i]->GetX() < mouseX && mouseX < gameObjects[i]->GetX() + gameObjects[i]->GetWidth() &&
					gameObjects[i]->GetY() < mouseY && mouseY < gameObjects[i]->GetY() + gameObjects[i]->GetHeight())
				{
					Inventory* tempInventory = dynamic_cast<InventoryUI*>(gameObjects[i])->GetInventory();
					dynamic_cast<InventoryUI*>(gameObjects[i])->SetInventory(this->inventory);
					this->SetInventory(tempInventory);
				}
			}	
			isDrag = false;
			SetX(originX);
			SetY(originY);
		}
	}

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
	if (!inventory || inventory->number == 0 || inventory->id == "empty")
	{
		bitmap.SetFrameIndexOfBitmap(0);
	}

	bitmap.SetFrameIndexOfBitmap(inventory->textureIndex);

	if (bagOpen)
	{
		showAmount();
	}
}

void InventoryUI::OnClick(vector<GameObject*>& gameObjects)
{
	isDrag = true;
	originX = x;
	originY = y;

	// select hand
	if (!bagOpen && !isBag)
	{
		this->mainCharacter->SetMainHandSelectedIndex(this->index);
	}
}


InventoryUI* InventoryUI::SetBag(bool isBag)
{
	this->isBag = isBag;

	return this;
}

InventoryUI* InventoryUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}

InventoryUI* InventoryUI::SetIndex(int index) {
	this->index = index;

	return this;
}



InventoriesUI* InventoriesUI::Init(MainCharacter* mainCharacter, vector<GameObject*>& gameObjects)
{
	GameObject::Init({ "resources/empty.bmp" })->SetPosition(100, 0);
	ItemsTable* itemsTable = new ItemsTable();

	this->mainCharacter = mainCharacter;
	// 快捷欄
	for (int i = 0; i < 6; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]
			->SetMainCharacter(mainCharacter)
			->SetIndex(i)
			->SetBag(false)
			->SetInventory(mainCharacter->GetInventory(i))->Init(itemsTable->GetInventoryItemsPath())
			->SetPosition(166 + (float)i * 52, 408.0f)
			->SetUI(true)
			->SetActive(true)
			->SetUI(true)
			->SetActive(true)
			->SetId("inventory");
		gameObjects.push_back(inventoryUI[i]);
	}
	// 背包
	for (int i = 6; i < 24; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]
			->SetMainCharacter(mainCharacter)
			->SetIndex(i)
			->SetBag(true)
			->SetInventory(mainCharacter->GetInventory(i))
			->Init(itemsTable->GetInventoryItemsPath())
			->SetPosition(166 + (float)(i % 6) * 52, 168.0f + (float)(floor(i / 6) - 1) * 52)
			->SetUI(true)
			->SetActive(true)
			->SetId("inventory");
		gameObjects.push_back(inventoryUI[i]);
	}

	return this;
}
void InventoriesUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, int mouseX, int mouseY)
{
}
