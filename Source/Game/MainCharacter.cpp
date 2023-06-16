#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Block.h"
#include "Item.h"
#include <string>
#include "tool.h"

using namespace game_framework;

float roundTo48(float num)
{
	return ((int)(num / 48)) * 48.0f;
}

Inventory::Inventory()
{
	this->id = "empty";
	this->textureIndex = 0;
	this->number = 0;
}

MainCharacter::MainCharacter()
{
	useTable = false;
	for (unsigned int i = 0; i < 28; i++)
	{
		inventories[i] = new Inventory();
	}
}

MainCharacter* MainCharacter::Init(vector<string> filename)
{
	GameObject::Init(filename);

	for (unsigned int i = 0; i < 28; i++)
	{
		inventories[i] = new Inventory();
		inventories[i]->id = "empty";
		inventories[i]->textureIndex = 0;
		inventories[i]->number = 0;
	}
	return this;
}

void MainCharacter::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	GameObject::OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	OnAttack(pressedKeys, gameObjects);
	OnMove(pressedKeys, gameObjects);
	OnHurt(pressedKeys, gameObjects);

	if (keyFind(pressedKeys, "1"))
	{
		OnBuild(gameObjects);
		OnFillWater(gameObjects);
		OnDrink(gameObjects);
		OnEat(gameObjects);
	}

	if (keyFind(pressedKeys, "E"))
	{
		SetUseTable(false);
	}

	// every 7200 frame romve 100f
	SetThirsty(GetThirsty() - 0.01851851851f);
	// every 7200 frame romve 100f
	SetHungry(GetHungry() - 0.01851851851f);

	if (GetThirsty() <= 0 || GetHungry() <= 0)
	{
		SetHp(GetHp() - 0.1f);
	}

	if (GetThirsty() >= 95.0f || GetHungry() >= 95.0f && GetHp() < 100.0f)
	{
		SetHp(GetHp() + 0.01388888888f);
	}
}

void MainCharacter::OnMove(string pressedKeys, vector<GameObject*>& gameObjects)
{

	if (moveSoundTick > 0) {
		moveSoundTick--;
	}


	if (motionX > 0.01f || motionX < -0.01f)
	{
		motionX *= 0.8f;
	}
	else
	{
		motionX = 0;
	}

	if (motionY > 0.01f || motionY < -0.01f)
	{
		motionY *= 0.8f;
	}
	else
	{
		motionY = 0;
	}

	bool colliderFlag = false;
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == this)
		{
			continue;
		}

		if (gameObjects[i]->isTriggerWith(this) && dynamic_cast<Item*>(gameObjects[i]))
		{
			Item* item = dynamic_cast<Item*>(gameObjects[i]);
			CAudio::Instance()->Play(2001, false);

			addItemToInventory(item);
			item->Destroy(gameObjects);
			continue;
		}

		if (gameObjects[i]->isCollideWith(this))
		{

			float overlapX = ((gameObjects[i]->GetX() + gameObjects[i]->GetWidth() / 2) - (this->GetX() + this->GetWidth() / 2)) / (gameObjects[i]->GetWidth() / 2 + this->GetWidth() / 2);
			float overlapY = ((gameObjects[i]->GetY() + gameObjects[i]->GetHeight() / 2) - (this->GetY() + this->GetHeight() / 2)) / (gameObjects[i]->GetHeight() / 2 + this->GetHeight() / 2);

			if (overlapX < 0.5)
			{
				motionX = -overlapX;
			}
			else if (overlapX < 0.5)
			{
				motionX *= 0.8f;
				motionX -= ((1 - abs(overlapY)) * overlapX);
			}
			else
			{
				motionX -= ((1 - abs(overlapY)) * overlapX);
			}

			if (motionY < 0.5)
			{
				motionY = -overlapY;
			}
			else if (motionY < 0.5)
			{
				motionY *= 0.8f;
				motionY -= ((1 - abs(overlapX)) * overlapY);
			}
			else
			{
				motionY -= ((1 - abs(overlapX)) * overlapY) * 0.01f;
			}
			colliderFlag = true;
			continue;
		}
	}

	if (colliderFlag)
	{
		return;
	}
	if (keyFind(pressedKeys, "W"))
	{
		GoTop();
		OnMoveSound();
	}
	else if (keyFind(pressedKeys, "S"))
	{
		GoBottom();
		OnMoveSound();
	}

	if (keyFind(pressedKeys, "A"))
	{
		GoLeft();
		OnMoveSound();
	}
	else if (keyFind(pressedKeys, "D"))
	{
		GoRight();
		OnMoveSound();
	}

	if (GetX() + motionX < 0)
	{
		motionX = 1;
	}
	if (GetX() + motionX > 976)
	{
		motionX = -1;
	}
	if (GetY() + motionY < 0)
	{
		motionY = 1;
	}
	if (GetY() + motionY > 976)
	{
		motionY = -1;
	}
}


void MainCharacter::OnMoveSound() {
	if (moveSoundTick <= 0) {
		moveSoundTick = 40;
		int randNum = rand() % 3;

		switch (randNum) {
		case 0:
			CAudio::Instance()->Play(1001, false);
			break;
		case 1:
			CAudio::Instance()->Play(1002, false);
			break;
		case 2:
			CAudio::Instance()->Play(1003, false);
			break;
		}
	}



	bool frame = moveAnimTick < 10;
	moveAnimTick++;
	if (moveAnimTick > 20) {
		moveAnimTick = 0;
	}
	if (motionX >= 0) {
		bitmap.SetFrameIndexOfBitmap(frame ? 1 : 0);
	}
	else {
		bitmap.SetFrameIndexOfBitmap(frame ? 3 : 2);
	}
}

void MainCharacter::OnAttack(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (useTable || useWaterPurifier || keyFind(pressedKeys, "E") || !keyFind(pressedKeys, "0"))
	{
		return;
	}
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == this)
		{
			continue;
		}

		const float x = this->GetX() - 16;
		const float y = this->GetY() - 16;
		const float width = this->GetWidth() + 32;
		const float height = this->GetHeight() + 32;
		const float objX = (*gameObjects[i]).GetX();
		const float objY = (*gameObjects[i]).GetY();
		const float objWidth = (*gameObjects[i]).GetWidth();
		const float objHeight = (*gameObjects[i]).GetHeight();

		if (x + width < objX || x > objX + objWidth)
		{
			continue;
		}

		if (y + height < objY || y > objY + objHeight)
		{
			continue;
		}
		Attack(gameObjects[i]);
	}
}

void MainCharacter::OnHurt(string pressedKeys, vector<GameObject*>& gameObjects)
{
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

void MainCharacter::OnBuild(vector<GameObject*>& gameObjects)
{
	if (terrian->IsBlock(GetX(), GetY()))
	{
		return;
	}

	bool isPutBlock = false;
	if (inventories[mainHandSelectedIndex]->id == "craft_table")
	{
		this->terrian->SetBlock(GetX(), GetY(), 7);
		isPutBlock = true;
	}


	if (inventories[mainHandSelectedIndex]->id == "water_purifier")
	{
		this->terrian->SetBlock(GetX(), GetY(), 10);
		isPutBlock = true;
	}

	if (inventories[mainHandSelectedIndex]->id == "sapling")
	{
		this->terrian->SetBlock(GetX(), GetY(), 2);
		isPutBlock = true;
	}

	if (inventories[mainHandSelectedIndex]->id == "campfire")
	{
		this->terrian->SetBlock(GetX(), GetY(), 11);
		isPutBlock = true;
	}


	if (isPutBlock) {
		CAudio::Instance()->Play(1011, false);
		inventories[mainHandSelectedIndex]->number -= 1;
		if (inventories[mainHandSelectedIndex]->number == 0)
		{
			inventories[mainHandSelectedIndex]->id = "empty";
			inventories[mainHandSelectedIndex]->textureIndex = 0;
		}
	}
}

void MainCharacter::OnFillWater(vector<GameObject*>& gameObjects)
{
	if (inventories[mainHandSelectedIndex]->id != "empty_bottle")
	{
		return;
	}

	if (!terrian->IsBehindWater(GetX(), GetY()))
	{
		return;
	}


	inventories[mainHandSelectedIndex]->number -= 1;
	if (inventories[mainHandSelectedIndex]->number == 0)
	{
		inventories[mainHandSelectedIndex]->id = "empty";
		inventories[mainHandSelectedIndex]->textureIndex = 0;
	}
	CAudio::Instance()->Play(2001, false);

	ItemTable* itemTable = new ItemTable("dirty_water_bottle", "resources/dirty_water_bottle.bmp", 1, 1);
	Item* item = new Item();
	item->Init({ itemTable->path })
		->SetId(itemTable->id)
		->SetActive(true);

	addItemToInventory(item);
	delete itemTable;
	delete item;
}

void MainCharacter::OnBarbecue(vector<GameObject*>& gameObjects)
{
	if (inventories[mainHandSelectedIndex]->id != "raw_meat")
	{
		return;
	}

	inventories[mainHandSelectedIndex]->number -= 1;
	if (inventories[mainHandSelectedIndex]->number == 0)
	{
		inventories[mainHandSelectedIndex]->id = "empty";
		inventories[mainHandSelectedIndex]->textureIndex = 0;
	}
	CAudio::Instance()->Play(2001, false);

	ItemTable* itemTable = new ItemTable("cooked_meat", "resources/cooked_meat.bmp", 1, 1);
	Item* item = new Item();
	item->Init({ itemTable->path })
		->SetId(itemTable->id)
		->SetActive(true);

	addItemToInventory(item);


	delete itemTable;
	delete item;

}

void MainCharacter::OnDrink(vector<GameObject*>& gameObjects)
{
	if (inventories[mainHandSelectedIndex]->id == "clean_water_bottle")
	{
		inventories[mainHandSelectedIndex]->number -= 1;
		if (inventories[mainHandSelectedIndex]->number == 0)
		{
			inventories[mainHandSelectedIndex]->id = "empty";
			inventories[mainHandSelectedIndex]->textureIndex = 0;
		}

		const float newThirsty = GetThirsty() + 10.0f;
		SetThirsty(newThirsty > 100.0f ? 100.0f : newThirsty);


		ItemTable* itemTable = new ItemTable("empty_bottle", "resources/empty_bottle.bmp", 1, 1);
		Item* item = new Item();
		item->Init({ itemTable->path })
			->SetId(itemTable->id)
			->SetActive(true);

		addItemToInventory(item);

		delete itemTable;
		delete item;
	}
}

void MainCharacter::OnEat(vector<GameObject*>& gameObjects)
{
	if (inventories[mainHandSelectedIndex]->id == "apple")
	{
		inventories[mainHandSelectedIndex]->number -= 1;
		if (inventories[mainHandSelectedIndex]->number == 0)
		{
			inventories[mainHandSelectedIndex]->id = "empty";
			inventories[mainHandSelectedIndex]->textureIndex = 0;
		}

		const float newThirsty = GetThirsty() + 5.0f;
		SetThirsty(newThirsty > 100.0f ? 100.0f : newThirsty);

		const float newHungry = GetHungry() + 10.0f;
		SetHungry(newHungry > 100.0f ? 100.0f : newHungry);
	}


	if (inventories[mainHandSelectedIndex]->id == "cooked_meat")
	{
		inventories[mainHandSelectedIndex]->number -= 1;
		if (inventories[mainHandSelectedIndex]->number == 0)
		{
			inventories[mainHandSelectedIndex]->id = "empty";
			inventories[mainHandSelectedIndex]->textureIndex = 0;
		}

		const float newHungry = GetHungry() + 20.0f;
		SetHungry(newHungry > 100.0f ? 100.0f : newHungry);
	}
}

void MainCharacter::Attack(GameObject* gameObject)
{
	if (dynamic_cast<Block*>(gameObject))
	{
		dynamic_cast<Block*>(gameObject)->OnAttacked(this);
	}
	else if (dynamic_cast<Enemy*>(gameObject))
	{
		dynamic_cast<Enemy*>(gameObject)->OnAttacked(this);
	}
}

void MainCharacter::OnAttacked(GameObject* gameObject)
{

	if (onAttackedTick <= 0)
	{
		CAudio::Instance()->Play(2003, false);

		hp -= 6 + rand() % 12;
		onAttackedTick = 15.0f; // 0.25 second
		centerX = this->GetX();
		centerY = this->GetY();
	}
}

float MainCharacter::GetHp()
{
	return hp;
}
float MainCharacter::GetHungry()
{
	return hungry;
}
float MainCharacter::GetThirsty()
{
	return thirsty;
}

void MainCharacter::addItemToInventory(Item* item)
{
	ItemsTable* itemsTable = new ItemsTable();
	for (unsigned int i = 0; i < 28; i++)
	{
		if (inventories[i]->id == item->GetId() && inventories[i]->number < 99)
		{
			inventories[i]->number++;
			return;
		}
	}

	for (unsigned int i = 0; i < 28; i++)
	{
		if (inventories[i]->id == "empty" || inventories[i]->number == 0)

		{
			inventories[i]->id = item->GetId();
			// this number is mean the texture index of item
			inventories[i]->textureIndex = itemsTable->GetInventoryItemById(item->GetId())->number;
			inventories[i]->number = 1;
			return;
		}
	}
}

MainCharacter* MainCharacter::SetInventory(int index, Inventory* _inventory) {
	inventories[index] = _inventory;
	return this;
}

MainCharacter* game_framework::MainCharacter::SetHp(float _hp)
{
	hp = _hp;
	return this;
}

MainCharacter* game_framework::MainCharacter::SetHungry(float _hungry)
{
	hungry = _hungry;
	return this;
}

MainCharacter* game_framework::MainCharacter::SetThirsty(float _thirsty)
{
	thirsty = _thirsty;
	return this;
}

Inventory* MainCharacter::GetInventory(int i)
{
	return inventories[i];
}

int MainCharacter::GetMainHandSelectedIndex()
{
	return mainHandSelectedIndex;
}

MainCharacter* MainCharacter::SetMainHandSelectedIndex(int newIndex)
{
	mainHandSelectedIndex = newIndex;

	return this;
}

MainCharacter* MainCharacter::SetTerrian(Terrian* terrian)
{
	this->terrian = terrian;
	return this;
}

MainCharacter* game_framework::MainCharacter::SetUseTable(bool _useTable)
{
	useWaterPurifier = false;
	useTable = _useTable;
	return this;
}


MainCharacter* game_framework::MainCharacter::SetUseWaterPurifier(bool _useWaterPurifier)
{
	useTable = false;
	useWaterPurifier = _useWaterPurifier;
	return this;
}

bool game_framework::MainCharacter::GetUseTable()
{
	return useTable;
}

bool game_framework::MainCharacter::GetUseWaterPurifier()
{
	return useWaterPurifier;
}
