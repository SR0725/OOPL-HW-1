#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "craftItem.h"
#include "Item.h"
#include <string>
#include "tool.h"
#include "MainCharacter.h"
#include <iostream>

using namespace game_framework;

CraftItem::CraftItem()
{
	isOpen = false;
	isOpenInTable = false;
	onlyTable = false;
	this->rawMaterials = vector<ItemTable*>();
	this->products = vector<ItemTable*>();
}

CraftItem* CraftItem::Init(vector<string> filename)
{
	GameObject::Init(filename);
	return this;
}

CraftItem* CraftItem::SetRawMaterials(vector<ItemTable*>& _rawMaterials) {
	rawMaterials = _rawMaterials;

	return this;
}


CraftItem* CraftItem::SetProducts(vector<ItemTable*>& _products)
{
	this->products = _products;
	return this;
}

void CraftItem::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (keyFind(pressedKeys, "E"))
	{
		isOpen = true;
	}
	else
	{
		isOpen = false;
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

	GameObject::Render(mainObject);
	bitmap.ShowBitmap();
}

void CraftItem::OnClick(vector<GameObject*>& gameObjects) {
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);


	// check raw material
	for (unsigned int i = 0; i < rawMaterials.size(); i++) {
		ItemTable* rawMaterial = rawMaterials[i];
		int characterRawMaterialNumber = 0;
		for (int j = 0; j < 24; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == rawMaterial->id) {
				characterRawMaterialNumber += inventory->number;
			}
			if (characterRawMaterialNumber >= rawMaterial->number) {
				break;
			}
		}


		if (characterRawMaterialNumber < rawMaterial->number) {
			return;
		}
	}

	// remove raw materials
	for (unsigned int i = 0; i < rawMaterials.size(); i++) {
		ItemTable* rawMaterial = rawMaterials[i];
		int alreadyRemoveMaterialNumber = 0;
		for (int j = 0; j < 24 && alreadyRemoveMaterialNumber < rawMaterial->number; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == rawMaterial->id) {
				if (inventory->number - rawMaterial->number + alreadyRemoveMaterialNumber > 0) {
					inventory->number -= (rawMaterial->number - alreadyRemoveMaterialNumber);
					if (inventory->number == 0) {
						inventory->id = "empty";
					}
					alreadyRemoveMaterialNumber = rawMaterial->number;
				}
				else {
					alreadyRemoveMaterialNumber += inventory->number;
					inventory->id = "empty";
					inventory->number = 0;
				}
			}
		}
	}

	// add products
	for (unsigned int i = 0; i < products.size(); i++) {
		ItemTable product = *products[i];

		int remainNumber = product.number;
		for (int j = 0; j < 24; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == product.id && inventory->number < 99)
			{
				if (inventory->number + remainNumber > 99) {
					remainNumber -= 99 - inventory->number;
					inventory->number = 99;
				}
				else {
					inventory->number += remainNumber;
					remainNumber = 0;
				}
				return;
			}
		}

		for (int j = 0; j < 24; j++)
		{
			Inventory* inventory = character->GetInventory(j);
			if (inventory->id == "empty")
			{
				inventory->id = product.id;
				if (product.id == "log")
				{
					inventory->textureIndex = 1;
				}
				else {
					inventory->textureIndex = 2;
				}
				inventory->number = remainNumber;
				return;
			}
		}
	}
}
