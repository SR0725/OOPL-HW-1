#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "craftTable.h"
#include "Item.h"
#include <string>
#include "tool.h"
#include "MainCharacter.h"
#include <iostream>
#include "config.h"

using namespace game_framework;

CraftItem::CraftItem()
{
	isOpen = false;
	isOpenInTable = false;
	onlyTable = false;
	this->rawMaterials = vector<ItemTable*>();
	this->products = vector<ItemTable*>();
}

CraftItem::~CraftItem()
{
	for (auto item : this->rawMaterials) {
		delete item;
	}
	for (auto item : this->products) {
		delete item;
	}
}


CraftItem* CraftItem::Init(vector<string> filename)
{
	GameObject::Init(filename);
	return this;
}

CraftItem* CraftItem::SetRawMaterials(vector<ItemTable*>& _rawMaterials)
{
	rawMaterials = _rawMaterials;

	return this;
}

CraftItem* CraftItem::SetProducts(vector<ItemTable*>& _products)
{
	this->products = _products;
	return this;
}

CraftItem* CraftItem::SetOnlyTable(bool onlyTable)
{
	this->onlyTable = onlyTable;

	return this;
}

CraftItem* CraftItem::SetOnlyWaterPurifier(bool onlyWaterPurifier)
{
	this->onlyWaterPurifier = onlyWaterPurifier;

	return this;
}

CraftItem* CraftItem::SetProductTitle(string _productTitle)
{
	this->productTitle = _productTitle;
	return this;
}

CraftItem* game_framework::CraftItem::SetRawMaterialTitle(string _rawMaterialsTitle)
{
	this->rawMaterialsTitle = _rawMaterialsTitle;
	return this;
}

void CraftItem::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

	if (character->GetUseTable())
	{
		isOpen = true;
		isOpenInTable = true;
		isOpenInWaterPurifier = false;
	}
	else if (character->GetUseWaterPurifier())
	{
		isOpen = true;
		isOpenInTable = false;
		isOpenInWaterPurifier = true;
	}
	else
	{
		if (keyFind(pressedKeys, "E"))
		{
			isOpen = true;
			isOpenInTable = false;
			isOpenInWaterPurifier = false;
		}
		else
		{
			isOpen = false;
		}
	}
}

void CraftItem::Render(GameObject* mainObject)
{
	if (!isOpen)
	{
		return;
	}
	if (onlyTable && !isOpenInTable)
	{
		return;
	}
	if ((!onlyWaterPurifier && isOpenInWaterPurifier) || (onlyWaterPurifier && !isOpenInWaterPurifier))
	{
		return;
	}

	GameObject::Render(mainObject);
	bitmap.ShowBitmap();
}

void CraftItem::OnClick(vector<GameObject*>& gameObjects)
{
	if (!isOpen)
	{
		return;
	}
	if (onlyTable && !isOpenInTable)
	{
		return;
	}
	if ((!onlyWaterPurifier && isOpenInWaterPurifier) || (onlyWaterPurifier && !isOpenInWaterPurifier))
	{
		return;
	}

	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	ItemsTable* itemsTable = new ItemsTable();

	// check raw material
	for (unsigned int i = 0; i < rawMaterials.size(); i++)
	{
		ItemTable* rawMaterial = rawMaterials[i];
		int characterRawMaterialNumber = 0;
		for (int j = 0; j < 28; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == rawMaterial->id)
			{
				characterRawMaterialNumber += inventory->number;
			}
			if (characterRawMaterialNumber >= rawMaterial->number)
			{
				break;
			}
		}

		if (characterRawMaterialNumber < rawMaterial->number)
		{
			return;
		}
	}

	// remove raw materials
	for (unsigned int i = 0; i < rawMaterials.size(); i++)
	{
		ItemTable* rawMaterial = rawMaterials[i];
		int alreadyRemoveMaterialNumber = 0;
		for (int j = 0; j < 28 && alreadyRemoveMaterialNumber < rawMaterial->number; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == rawMaterial->id)
			{
				if (inventory->number - rawMaterial->number + alreadyRemoveMaterialNumber > 0)
				{
					inventory->number -= (rawMaterial->number - alreadyRemoveMaterialNumber);
					alreadyRemoveMaterialNumber = rawMaterial->number;
				}
				else
				{
					alreadyRemoveMaterialNumber += inventory->number;
					inventory->id = "empty";
					inventory->number = 0;
					inventory->textureIndex = 0;
				}
			}
		}
	}
	CAudio::Instance()->Play(2001, false);

	// add products
	for (unsigned int i = 0; i < products.size(); i++)
	{
		ItemTable product = *products[i];

		int remainNumber = product.number;
		for (int j = 0; j < 28; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == product.id && inventory->number < 99)
			{
				if (inventory->number + remainNumber > 99)
				{
					remainNumber -= 99 - inventory->number;
					inventory->number = 99;
				}
				else
				{
					inventory->number += remainNumber;
					remainNumber = 0;
				}
				return;
			}
		}

		for (int j = 0; j < 28; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == "empty")
			{
				inventory->id = product.id;
				inventory->textureIndex = itemsTable->GetInventoryItemById(product.id)->number;
				inventory->number = remainNumber;
				return;
			}
		}
	}
}


CraftTable::CraftTable()
{

}


CraftTable::~CraftTable()
{

}

CraftTable* CraftTable::Init(vector<GameObject*>& uiObjects)
{
	GameObject::Init({ "resources/empty.bmp" })->SetPosition(100, 0);

	craft_background
		->Init({ "resources/craft_ui.bmp", "resources/water_purifier_ui.bmp" })
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) - 72.0f, SIZE_Y - 618.0f)
		->SetActive(true)
		->SetUI(true);

	// craft table
	CraftItem* craftItem_craftTable = new CraftItem();
	CraftItem* craftItem_campfire = new CraftItem();

	CraftItem* craftItem_wood_axe = new CraftItem();
	CraftItem* craftItem_wood_pickaxe = new CraftItem();
	CraftItem* craftItem_wood_sword = new CraftItem();

	CraftItem* craftItem_stone_axe = new CraftItem();
	CraftItem* craftItem_stone_pickaxe = new CraftItem();
	CraftItem* craftItem_stone_sword = new CraftItem();

	CraftItem* craftItem_iron_axe = new CraftItem();
	CraftItem* craftItem_iron_pickaxe = new CraftItem();
	CraftItem* craftItem_iron_sword = new CraftItem();


	CraftItem* craftItem_bottle = new CraftItem();
	CraftItem* craftItem_water_purifier = new CraftItem();

	// water_purifier
	CraftItem* craftItem_clean_water_bottle = new CraftItem();

	int index = 0;
	craftItem_craftTable
		->Init({ "resources/craft_craft_table.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 6), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("craft_table", "resources/craft_table.bmp", 1, 1) }))
		->SetProductTitle("Crafting Table")
		->SetRawMaterialTitle("Log 6")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	craftItem_clean_water_bottle
		->SetOnlyWaterPurifier(true)
		->Init({ "resources/clean_water_bottle_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("dirty_water_bottle", "resources/dirty_water_bottle.bmp", 1, 1), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("clean_water_bottle", "resources/clean_water_bottle.bmp", 1, 1) }))
		->SetProductTitle("Bottle with Clean Water")
		->SetRawMaterialTitle("Dirty water Bottle")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);


	index = 1;
	craftItem_campfire
		->Init({ "resources/campfire_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 4), new ItemTable("coal", "resources/coal.bmp", 1, 4) }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("campfire", "resources/campfire.bmp", 1, 1), }))
		->SetProductTitle("Campfire")
		->SetRawMaterialTitle("Log 4, Coal 4")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 2;
	craftItem_bottle
		->SetOnlyTable(true)
		->Init({ "resources/empty_bottle_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("sand", "resources/sand.bmp", 1, 5), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("empty_bottle", "resources/empty_bottle.bmp", 1, 1) }))
		->SetProductTitle("Bottle")
		->SetRawMaterialTitle("Sand 5")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 3;
	craftItem_water_purifier
		->SetOnlyTable(true)
		->Init({ "resources/water_purifier_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 4), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("water_purifier", "resources/water_purifier.bmp", 1, 1) }))
		->SetProductTitle("Water Purifier")
		->SetRawMaterialTitle("Log 4")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);


	// wood tool
	index = 4;
	craftItem_wood_axe
		->SetOnlyTable(true)
		->Init({ "resources/wood_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 5), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("wood_axe", "resources/wood_axe.bmp", 1, 1), }))
		->SetProductTitle("Wood Axe")
		->SetRawMaterialTitle("Log 5")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 5;
	craftItem_wood_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/wood_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 5), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("wood_pickaxe", "resources/wood_pickaxe.bmp", 1, 1) }))
		->SetProductTitle("Wood Pickaxe")
		->SetRawMaterialTitle("Log 5")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 6;
	craftItem_wood_sword
		->SetOnlyTable(true)
		->Init({ "resources/wood_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("log", "resources/log.bmp", 1, 5), }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("wood_sword", "resources/wood_sword.bmp", 1, 1) }))
		->SetProductTitle("Wood Sword")
		->SetRawMaterialTitle("Log 5")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	// stone tool
	index = 7;
	craftItem_stone_axe
		->SetOnlyTable(true)
		->Init({ "resources/stone_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
					new ItemTable("stone", "resources/stone.bmp", 1, 5),
					new ItemTable("wood_axe", "resources/wood_axe.bmp", 1, 1),
				}))
				->SetProducts(
					vector<ItemTable*>({ new ItemTable("stone_axe", "resources/stone_axe.bmp", 1, 1) }))
		->SetProductTitle("Stone Axe")
		->SetRawMaterialTitle("Stone 5, Wood Axe 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 8;
	craftItem_stone_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/stone_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
					new ItemTable("stone", "resources/stone.bmp", 1, 5),
					new ItemTable("wood_pickaxe", "resources/wood_pickaxe.bmp", 1, 1),
				}))
				->SetProducts(
					vector<ItemTable*>({ new ItemTable("stone_pickaxe", "resources/stone_pickaxe.bmp", 1, 1) }))
		->SetProductTitle("Stone Pickaxe")
		->SetRawMaterialTitle("Stone 5, Wood Pickaxe 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 9;
	craftItem_stone_sword
		->SetOnlyTable(true)
		->Init({ "resources/stone_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("stone", "resources/stone.bmp", 1, 5),
													 new ItemTable("wood_sword", "resources/wood_sword.bmp", 1, 1) }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("stone_sword", "resources/stone_sword.bmp", 1, 1) }))
		->SetProductTitle("Stone Sword")
		->SetRawMaterialTitle("Stone 5, Wood Sword 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	// iron tool
	index = 10;
	craftItem_iron_axe
		->SetOnlyTable(true)
		->Init({ "resources/iron_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
					new ItemTable("iron", "resources/iron.bmp", 1, 5),
					new ItemTable("stone_axe", "resources/stone_axe.bmp", 1, 1),
				}))
				->SetProducts(
					vector<ItemTable*>({ new ItemTable("iron_axe", "resources/iron_axe.bmp", 1, 1) }))
		->SetProductTitle("Iron Axe")
		->SetRawMaterialTitle("Iron 5, Stone Axe 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 11;
	craftItem_iron_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/iron_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
					new ItemTable("iron", "resources/iron.bmp", 1, 5),
					new ItemTable("stone_pickaxe", "resources/stone_pickaxe.bmp", 1, 1),
				}))
				->SetProducts(
					vector<ItemTable*>({ new ItemTable("iron_pickaxe", "resources/iron_pickaxe.bmp", 1, 1) }))
		->SetProductTitle("Iron Pickaxe")
		->SetRawMaterialTitle("Iron 5, Stone Pickaxe 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);

	index = 12;
	craftItem_iron_sword
		->SetOnlyTable(true)
		->Init({ "resources/iron_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({ new ItemTable("iron", "resources/iron.bmp", 1, 5),
													 new ItemTable("stone_sword", "resources/stone_sword.bmp", 1, 1) }))
		->SetProducts(
			vector<ItemTable*>({ new ItemTable("iron_sword", "resources/iron_sword.bmp", 1, 1) }))
		->SetProductTitle("Iron Sword")
		->SetRawMaterialTitle("Iron 5, Stone Sword 1")
		->SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)(index % 7) * 52, SIZE_Y - 508.0f + (float)(floor(index / 7) - 1) * 52)
		->SetActive(true)
		->SetUI(true);


	uiObjects.push_back(craft_background);

	uiObjects.push_back(craftItem_craftTable);
	uiObjects.push_back(craftItem_clean_water_bottle);
	uiObjects.push_back(craftItem_campfire);
	uiObjects.push_back(craftItem_water_purifier);
	uiObjects.push_back(craftItem_bottle);
	uiObjects.push_back(craftItem_wood_axe);
	uiObjects.push_back(craftItem_wood_pickaxe);
	uiObjects.push_back(craftItem_wood_sword);
	uiObjects.push_back(craftItem_stone_axe);
	uiObjects.push_back(craftItem_stone_pickaxe);
	uiObjects.push_back(craftItem_stone_sword);
	uiObjects.push_back(craftItem_iron_axe);
	uiObjects.push_back(craftItem_iron_pickaxe);
	uiObjects.push_back(craftItem_iron_sword);


	craftItems = vector<CraftItem*>({
		craftItem_craftTable,
		craftItem_wood_axe,
		craftItem_wood_pickaxe,
		craftItem_wood_sword,
		craftItem_stone_axe,
		craftItem_stone_pickaxe,
		craftItem_stone_sword,
		craftItem_iron_axe,
		craftItem_iron_pickaxe,
		craftItem_iron_sword,
		craftItem_bottle,
		craftItem_water_purifier,
		craftItem_clean_water_bottle,
		craftItem_campfire
		});


	return this;
}

void CraftTable::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

	if (character->GetUseTable())
	{
		craft_background->SetActive(true);
		craft_background->bitmap.SetFrameIndexOfBitmap(0);
		isBagOpen = true;
		isTableOpen = true;
		isWaterPurifier = false;
	}
	else if (character->GetUseWaterPurifier())
	{
		craft_background->SetActive(true);
		craft_background->bitmap.SetFrameIndexOfBitmap(1);
		isBagOpen = true;
		isTableOpen = false;
		isWaterPurifier = true;
	}
	else
	{
		isTableOpen = false;
		isWaterPurifier = false;
		if (keyFind(pressedKeys, "E"))
		{
			craft_background->bitmap.SetFrameIndexOfBitmap(0);
			craft_background->SetActive(true);
			isBagOpen = true;
		}
		else
		{
			craft_background->SetActive(false);
			isBagOpen = false;
		}
	}

	if (isBagOpen) {

		for (unsigned int i = 0; i < craftItems.size(); i++)
		{
			CraftItem* item = craftItems[i];
			if (!isTableOpen && item->onlyTable) {
				continue;
			}
			if ((!item->onlyWaterPurifier && isWaterPurifier) || (item->onlyWaterPurifier && !isWaterPurifier)) {

				continue;
			}

			int x = (int)item->GetX();
			int y = (int)item->GetY();
			int width = (int)item->GetWidth();
			int height = (int)item->GetHeight();
			// 判斷滑鼠是否在物品上
			if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
			{
				showProductTitle = item->productTitle;
				showRawMaterialsTitle = item->rawMaterialsTitle;
				break;
			}
			showProductTitle = "";
			showRawMaterialsTitle = "";
		}
	}
}

void CraftTable::Render(GameObject* mainObject)
{
	if (isBagOpen)
	{
		ShowCraftInfo();
	}

	GameObject::Render(mainObject);
	bitmap.ShowBitmap();
}

void CraftTable::ShowCraftInfo()
{

	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 20, "Arial Black", RGB(160, 105, 49));
	CTextDraw::Print(pDC, SIZE_X / 2 - 182, SIZE_Y - 610, showProductTitle);
	CTextDraw::ChangeFontLog(pDC, 16, "Arial", RGB(69, 46, 38));
	CTextDraw::Print(pDC, SIZE_X / 2 - 182, SIZE_Y - 586, showRawMaterialsTitle);
	CDDraw::ReleaseBackCDC();
}
