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
#include "config.h"

using namespace game_framework;

Inventory* InventoryUI::GetInventory()
{
	return mainCharacter->GetInventory(index);
}


void InventoryUI::showAmount()
{
	Inventory* inventory = mainCharacter->GetInventory(index);
	if (!inventory || inventory->number == 0 || inventory->id == "empty")
	{
		return;
	}
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 12, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, (int)(x + GetWidth() - 16), (int)(y + GetHeight() - 16), std::to_string(inventory->number));
	CDDraw::ReleaseBackCDC();
}

void InventoryUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	Inventory* inventory = mainCharacter->GetInventory(index);

	if (isDrag)
	{
		if (keyFind(pressedKeys, "0"))
		{
			SetX((float)mouseX - GetWidth() / 2);
			SetY((float)mouseY - GetHeight() / 2);
		}
		else {
			// 取得所有其他物品欄位 看是否有重疊
			for (unsigned int i = 0; i < uiObjects.size(); i++)
			{
				if (uiObjects[i]->GetId() != "inventory")
				{
					continue;
				}
				if (uiObjects[i] == this)
				{
					continue;
				}
				if (uiObjects[i]->GetX() < mouseX && mouseX < uiObjects[i]->GetX() + uiObjects[i]->GetWidth() &&
					uiObjects[i]->GetY() < mouseY && mouseY < uiObjects[i]->GetY() + uiObjects[i]->GetHeight())
				{
					Inventory* tempInventory = mainCharacter->GetInventory(dynamic_cast<InventoryUI*>(uiObjects[i])->index);
					mainCharacter->SetInventory(dynamic_cast<InventoryUI*>(uiObjects[i])->index, inventory);
					mainCharacter->SetInventory(this->index, tempInventory);
				}
			}
			isDrag = false;
			SetX(originX);
			SetY(originY);
		}
	}

	if (mainCharacter->GetUseTable())
	{
		bagOpen = true;
	}
	else {
		if (keyFind(pressedKeys, "E"))
		{
			bagOpen = true;
		}
		else
		{
			bagOpen = false;
		}
	}
}

void InventoryUI::Render(GameObject* mainObject)
{
	Inventory* inventory = mainCharacter->GetInventory(index);

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
	if (bagOpen)
	{
		isDrag = true;
	}
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



InventoriesUI* InventoriesUI::Init(MainCharacter* mainCharacter, vector<GameObject*>& uiObjects)
{
	GameObject::Init({ "resources/empty.bmp" })->SetPosition(100, 0);
	ItemsTable* itemsTable = new ItemsTable();

	inventory_background
		->Init({ "resources/inventory_bg_ui.bmp" })
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) - 16.0f, SIZE_Y - 386.0f)
		->SetActive(true)
		->SetUI(true);
	uiObjects.push_back(inventory_background);

	this->mainCharacter = mainCharacter;
	// 快捷欄
	for (int i = 0; i < 7; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]
			->SetMainCharacter(mainCharacter)
			->SetIndex(i)
			->SetBag(false)
			->Init(itemsTable->GetInventoryItemsPath())
			->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)i * 52, SIZE_Y - 72.0f)
			->SetUI(true)
			->SetActive(true)
			->SetUI(true)
			->SetActive(true)
			->SetId("inventory");
		uiObjects.push_back(inventoryUI[i]);
	}
	// 背包
	for (int i = 7; i < 28; i++)
	{
		inventoryUI[i] = new InventoryUI();
		inventoryUI[i]
			->SetMainCharacter(mainCharacter)
			->SetIndex(i)
			->SetBag(true)
			->Init(itemsTable->GetInventoryItemsPath())
			->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(i % 7) * 52, SIZE_Y - 358.0f +(float)(floor(i / 7) - 1) * 52)
			->SetUI(true)
			->SetActive(true)
			->SetId("inventory");
		uiObjects.push_back(inventoryUI[i]);
	}

	return this;
}
void InventoriesUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

	if (character->GetUseTable())
	{
		isBagOpen = true;
		inventory_background->SetActive(true);

	}
	else
	{
		if (keyFind(pressedKeys, "E"))
		{
			isBagOpen = true;
			inventory_background->SetActive(true);
		}
		else
		{
			isBagOpen = false;
			inventory_background->SetActive(false);
		}
	}

	if (isBagOpen)
	{
		for (unsigned int i = 0; i < 28; i++)
		{
			InventoryUI* inventory = inventoryUI[i];
			int x = (int)inventory->GetX();
			int y = (int)inventory->GetY();
			int width = (int)inventory->GetWidth();
			int height = (int)inventory->GetHeight();
			// 判斷滑鼠是否在物品上
			if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
			{
				if (inventory->GetInventory()->id == "empty") {
					showInventoryTitle = "";
				}
				else {
					showInventoryTitle = inventory->GetInventory()->id;
				}
				break;
			}
			showInventoryTitle = "";
		}
	}
}

void InventoriesUI::Render(GameObject* mainObject)
{
	if (isBagOpen)
	{
		ShowInventoryInfo();
	}

	GameObject::Render(mainObject);
}

void InventoriesUI::ShowInventoryInfo()
{
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 16, "Arial Black", RGB(160, 105, 49));
	CTextDraw::Print(pDC, SIZE_X / 2 - 182, SIZE_Y - 386, showInventoryTitle);
	CDDraw::ReleaseBackCDC();
}
