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
		});
	this->inventoryItems = new vector<ItemTable*>({
		new ItemTable("empty", "resources/empty.bmp", 0, 0),
		new ItemTable("log", "resources/log_inventory.bmp", 0, 1),
		new ItemTable("stone", "resources/stone_inventory.bmp", 0, 2),
		new ItemTable("coal", "resources/coal_inventory.bmp", 0, 3),
		new ItemTable("iron", "resources/iron_inventory.bmp", 0, 4),
		new ItemTable("slive", "resources/slive_inventory.bmp", 0, 5),
		new ItemTable("apple", "resources/apple_inventory.bmp", 0, 6),
		new ItemTable("apple_sapling", "resources/apple_sapling_inventory.bmp", 0, 7),
		new ItemTable("sapling", "resources/sapling_inventory.bmp", 0, 8),
		new ItemTable("craft_table", "resources/craft_table_inventory.bmp", 0, 9),
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

ItemTable* game_framework::ItemsTable::GetItemById(string id)
{
	for (unsigned int i = 0; i < this->items->size(); i++)
	{
		if (this->items->at(i)->id == id)
		{
			return this->inventoryItems->at(i);
		}
	}
	return NULL;
}

ItemTable* game_framework::ItemsTable::GetInventoryItemById(string id)
{
	for (unsigned int i = 0; i < this->inventoryItems->size(); i++)
	{
		if (this->inventoryItems->at(i)->id == id)
		{
			return this->inventoryItems->at(i);
		}
	}
	return NULL;
}



Item::Item()
{
}

void Item::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
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
