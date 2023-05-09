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

Inventory::Inventory()
{
	this->id = "empty";
	this->textureIndex = 0;
	this->number = 0;
}


MainCharacter::MainCharacter()
{
	for (unsigned int i = 0; i < 24; i++)
	{
		inventories[i] = Inventory();
	}
}

MainCharacter* MainCharacter::Init(vector<string> filename)
{
	GameObject::Init(filename);
	return this;
}

void MainCharacter::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
{
	GameObject::OnUpdate(pressedKeys, gameObjects);
	OnAttack(pressedKeys, gameObjects);
	OnMove(pressedKeys, gameObjects);
	OnHurt(pressedKeys, gameObjects);
}

void MainCharacter::OnMove(string pressedKeys, vector<GameObject*>& gameObjects)
{
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
			OnGetItem(dynamic_cast<Item*>(gameObjects[i]), gameObjects);
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
	}
	else if (keyFind(pressedKeys, "S"))
	{
		GoBottom();
	}
	if (keyFind(pressedKeys, "A"))
	{
		GoLeft();
	}
	else if (keyFind(pressedKeys, "D"))
	{
		GoRight();
	}
}

void MainCharacter::OnGetItem(Item* item, vector<GameObject*>& gameObjects)
{
	if (item->GetId() == "log")
	{
		addItemToInventory(item);
		item->Destroy(gameObjects);
	}
}

void MainCharacter::OnAttack(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (!keyFind(pressedKeys, "0"))
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
		hp -= 5;
		onAttackedTick = 15.0f; // 0.25 second
		centerX = this->GetX();
		centerY = this->GetY();
	}
}

float MainCharacter::GetHp()
{
	return hp;
}

void MainCharacter::addItemToInventory(Item* item)
{
	ItemsTable* itemsTable = new ItemsTable();
	for (unsigned int i = 0; i < 24; i++)
	{
		if (inventories[i].id == item->GetId() && inventories[i].number < 99)
		{
			inventories[i].number++;
			return;
		}
	}

	for (unsigned int i = 0; i < 24; i++)
	{
		if (inventories[i].id == "empty")
		{
			inventories[i].id = item->GetId();
			if (item->GetId() == "log")
			{
				inventories[i].textureIndex = 1;
			}
			inventories[i].number = 1;
			return;
		}
	}
}

Inventory* MainCharacter::GetInventory(int i)
{
	return &inventories[i];
}