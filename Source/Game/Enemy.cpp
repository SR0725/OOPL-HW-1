#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "Enemy.h"
#include "MainCharacter.h"
#include "Item.h"
#include "Block.h"
#include <string>
#include "tool.h"

using namespace game_framework;

Enemy* Enemy::Init(vector<string> filename)
{
	GameObject::Init(filename);

	return this;
}

Enemy* Enemy::SetHp(float _hp)
{
	hp = _hp;

	return this;
}

Enemy* Enemy::SetAttack(float _attack)
{
	attack = _attack;

	return this;
}

Enemy* Enemy::SetDefense(float _defence)
{
	defense = _defence;

	return this;
}

void Enemy::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	GameObject::OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	OnMove(pressedKeys, gameObjects);
	OnAttack(pressedKeys, gameObjects);
	OnHurt(pressedKeys, gameObjects);
}

void Enemy::OnHurt(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (hp <= 0)
	{
		this->OnDropItem(gameObjects);
		this->Destroy(gameObjects);
		return;
	}
	if (onAttackedTick > 0)
	{
		onAttackedTick -= 1.0f;
	}
}

void Enemy::OnMove(string pressedKeys, vector<GameObject*>& gameObjects)
{

	bool frame = moveAnimTick < 20;
	moveAnimTick ++;
	if (moveAnimTick > 40) {
		moveAnimTick = 0;
	}
	if (motionX >= 0) {
		bitmap.SetFrameIndexOfBitmap(frame ? 1 : 0);
	}
	else {
		bitmap.SetFrameIndexOfBitmap(frame ? 3 : 2);
	}


	if (onAttackedTick > 0)
	{
		return;
	}

	MainCharacter* mainCharacter;

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetId() == "MainCharacter")
		{
			mainCharacter = (MainCharacter*)gameObjects[i];
			break;
		}
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

	if (mainCharacter->GetX() > GetX())
	{
		GoRight();
	}
	else
	{
		GoLeft();
	}

	if (mainCharacter->GetY() > GetY())
	{
		GoBottom();
	}
	else
	{
		GoTop();
	}
}

void Enemy::OnAttack(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (onAttackedTick > 0)
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

void Enemy::Attack(GameObject* gameObject)
{
	if (dynamic_cast<MainCharacter*>(gameObject))
	{
		dynamic_cast<MainCharacter*>(gameObject)->OnAttacked(this);
	}
	else if (dynamic_cast<Block*>(gameObject))
	{
		Block* block = dynamic_cast<Block*>(gameObject);
		if (block->GetId() != "tree_block" && block->GetId() != "tree_small_block" && block->GetId() != "craft_table" && block->GetId() != "water_purifier_block" && block->GetId() != "campfire_block") {
			return;
		}
		dynamic_cast<Block*>(gameObject)->OnAttacked(this);
	}
}

void Enemy::OnAttacked(GameObject* gameObject)
{
	if (onAttackedTick > 0)
	{
		return;
	}
	float damage = 1.0;
	if (dynamic_cast<MainCharacter*>(gameObject))
	{
		MainCharacter* player = dynamic_cast<MainCharacter*>(gameObject);
		string useTool = player->GetInventory(player->GetMainHandSelectedIndex())->id;

		damage = player->attack;

		if (useTool == "wood_sword") {
			CAudio::Instance()->Play(1012, false);
			damage = 2 * player->attack;
		}
		else if (useTool == "stone_sword") {
			CAudio::Instance()->Play(1013, false);
			damage = 3 * player->attack;
		}
		else if (useTool == "iron_sword") {
			CAudio::Instance()->Play(1014, false);
			damage = 4 * player->attack;
		}
		else {
			CAudio::Instance()->Play(1015, false);
		}
	}
	hp -= damage;
	onAttackedTick = 8.0f; // 0.3 second
	motionY = -((gameObject->GetY() + gameObject->GetHeight() / 2) - (GetY() + GetHeight() / 2)) / (gameObject->GetHeight() + 32.0f) * 6.0f;
	motionX = -((gameObject->GetX() + gameObject->GetWidth() / 2) - (GetX() + GetWidth() / 2)) / (gameObject->GetWidth() + 32.0f) * 6.0f;

}

float Enemy::GetHp()
{
	return hp;
}


Enemy* Enemy::SetDropItems(vector<ItemTable*>* _dropItems)
{
	dropItems = _dropItems;

	return this;
}


Enemy* Enemy::OnDropItem(vector<GameObject*>& gameObjects)
{
	for (unsigned int i = 0; i < dropItems->size(); i++)
	{
		ItemTable* itemTable = dropItems->at(i);

		if (itemTable->rate * 10000 < random(0.0f, 9999.0f))
		{
			continue;
		}

		for (int j = 0; j < itemTable->number; j++)
		{
			Item* item = new Item();
			item->Init({ itemTable->path })
				->SetPosition(this->GetX() + random(-16.0f, 16.0f), this->GetY() + random(-16.0f, 16.0f))
				->SetTrigger(true)
				->SetId(itemTable->id)
				->SetActive(true);
			gameObjects.push_back(item);
		}
	}
	return this;
}
