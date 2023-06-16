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

ItemsTable::~ItemsTable() {
	for (auto item : *this->items) {
		delete item;
	}
	delete this->items;

	for (auto item : *this->inventoryItems) {
		delete item;
	}
	delete this->inventoryItems;
}

ItemsTable::ItemsTable()
{
	this->items = new vector<ItemTable*>({
		new ItemTable("empty", "resources/empty.bmp", 0, 0),
		new ItemTable("log", "resources/log.bmp", 0, 1),
		new ItemTable("stone", "resources/stone.bmp", 0, 2),
		new ItemTable("coal", "resources/coal.bmp", 0, 3),
		new ItemTable("iron", "resources/iron.bmp", 0, 4),
		new ItemTable("slive", "resources/slive.bmp", 0, 5),
		new ItemTable("apple", "resources/apple.bmp", 0, 6),
		new ItemTable("apple_sapling", "resources/apple_sapling.bmp", 0, 7),
		new ItemTable("sapling", "resources/sapling.bmp", 0, 8),
		new ItemTable("craft_table", "resources/craft_table.bmp", 0, 9),
		new ItemTable("wood_axe", "resources/wood_axe.bmp", 0, 10),
		new ItemTable("wood_pickaxe", "resources/wood_pickaxe.bmp", 0, 11),
		new ItemTable("wood_sword", "resources/wood_sword.bmp", 0, 12),
		new ItemTable("stone_axe", "resources/stone_axe.bmp", 0, 13),
		new ItemTable("stone_pickaxe", "resources/stone_pickaxe.bmp", 0, 14),
		new ItemTable("stone_sword", "resources/stone_sword.bmp", 0, 15),
		new ItemTable("iron_axe", "resources/iron_axe.bmp", 0, 16),
		new ItemTable("iron_pickaxe", "resources/iron_pickaxe.bmp", 0, 17),
		new ItemTable("iron_sword", "resources/iron_sword.bmp", 0, 18),
		new ItemTable("sand", "resources/sand.bmp", 0, 19),
		new ItemTable("empty_bottle", "resources/empty_bottle.bmp", 0, 20),
		new ItemTable("dirty_water_bottle", "resources/dirty_water_bottle.bmp", 0, 21),
		new ItemTable("clean_water_bottle", "resources/clean_water_bottle.bmp", 0, 22),
		new ItemTable("water_purifier", "resources/water_purifier.bmp", 0, 23),
		new ItemTable("raw_meat", "resources/raw_meat.bmp", 0, 24),
		new ItemTable("cooked_meat", "resources/cooked_meat.bmp", 0, 25),
		new ItemTable("campfire", "resources/campfire.bmp", 0, 26),
		});
	this->inventoryItems = new vector<ItemTable*>({
		new ItemTable("empty", "resources/empty_inventory.bmp", 0, 0),
		new ItemTable("log", "resources/log_inventory.bmp", 0, 1),
		new ItemTable("stone", "resources/stone_inventory.bmp", 0, 2),
		new ItemTable("coal", "resources/coal_inventory.bmp", 0, 3),
		new ItemTable("iron", "resources/iron_inventory.bmp", 0, 4),
		new ItemTable("slive", "resources/slive_inventory.bmp", 0, 5),
		new ItemTable("apple", "resources/apple_inventory.bmp", 0, 6),
		new ItemTable("apple_sapling", "resources/apple_sapling_inventory.bmp", 0, 7),
		new ItemTable("sapling", "resources/sapling_inventory.bmp", 0, 8),
		new ItemTable("craft_table", "resources/craft_table_inventory.bmp", 0, 9),
		new ItemTable("wood_axe", "resources/wood_axe_inventory.bmp", 0, 10),
		new ItemTable("wood_pickaxe", "resources/wood_pickaxe_inventory.bmp", 0, 11),
		new ItemTable("wood_sword", "resources/wood_sword_inventory.bmp", 0, 12),
		new ItemTable("stone_axe", "resources/stone_axe_inventory.bmp", 0, 13),
		new ItemTable("stone_pickaxe", "resources/stone_pickaxe_inventory.bmp", 0, 14),
		new ItemTable("stone_sword", "resources/stone_sword_inventory.bmp", 0, 15),
		new ItemTable("iron_axe", "resources/iron_axe_inventory.bmp", 0, 16),
		new ItemTable("iron_pickaxe", "resources/iron_pickaxe_inventory.bmp", 0, 17),
		new ItemTable("iron_sword", "resources/iron_sword_inventory.bmp", 0, 18),
		new ItemTable("sand", "resources/sand_inventory.bmp", 0, 19),
		new ItemTable("empty_bottle", "resources/empty_bottle_inventory.bmp", 0, 20),
		new ItemTable("dirty_water_bottle", "resources/dirty_water_bottle_inventory.bmp", 0, 21),
		new ItemTable("clean_water_bottle", "resources/clean_water_bottle_inventory.bmp", 0, 22),
		new ItemTable("water_purifier", "resources/water_purifier_inventory.bmp", 0, 23),
		new ItemTable("raw_meat", "resources/raw_meat_inventory.bmp", 0, 24),
		new ItemTable("cooked_meat", "resources/cooked_meat_inventory.bmp", 0, 25),
		new ItemTable("campfire", "resources/campfire_inventory.bmp", 0, 26),
		});

	if (this->items->size() != this->inventoryItems->size())
	{
		throw "Items Table is not same with inventoryItems Table";
	}

	for (unsigned int i = 0; i < this->items->size(); i++)
	{
		if (this->items->at(i)->id != this->inventoryItems->at(i)->id)
		{
			throw "Items Table is not same with inventoryItems Table";
		}
	}
}

ItemTable* ItemsTable::GetItemById(string id)
{
	for (unsigned int i = 0; i < this->items->size(); i++)
	{
		if (this->items->at(i)->id == id)
		{
			return this->inventoryItems->at(i);
		}
	}
	return new ItemTable("empty", "resources/empty", 0, 0);
}

ItemTable* ItemsTable::GetInventoryItemById(string id)
{
	for (unsigned int i = 0; i < this->inventoryItems->size(); i++)
	{
		if (this->inventoryItems->at(i)->id == id)
		{
			return this->inventoryItems->at(i);
		}
	}
	return new ItemTable("empty", "resources/empty_inventory.bmp", 0, 0);
}

vector<string> ItemsTable::GetInventoryItemsPath()
{
	vector<string> result;
	for (unsigned int i = 0; i < this->inventoryItems->size(); i++)
	{
		result.push_back(this->inventoryItems->at(i)->path);
	}
	return result;
}



Item::Item()
{
}

void Item::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
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
