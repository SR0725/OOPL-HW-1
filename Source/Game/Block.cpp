#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "Item.h"
#include "Block.h"
#include <string>
#include "tool.h"

using namespace game_framework;

Block::Block()
{
	hp = 10;
	onAttackedTick = 0;
	centerX = -9999;
	centerY = -9999;
	dropItems = vector<ItemTable*>();
}

Block* Block::Init(vector<string> filename) {
	GameObject::Init(filename);
	return this;
}

void Block::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects)
{
	if (hp <= 0)
	{
		OnDropItem(gameObjects);
		Destroy(gameObjects);
		return;
	}

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

void Block::OnAttacked(GameObject* gameObject)
{
	if (onAttackedTick <= 0)
	{
		hp -= 5;
		onAttackedTick = 60.0f; // 1 second
		centerX = this->GetX();
		centerY = this->GetY();
	}
}

Block* Block::SetDropItems(vector<ItemTable*>& _dropItems) {
	dropItems = _dropItems;

	return this;
}

Block* Block::OnDropItem(vector<GameObject*>& gameObjects) {
	for (unsigned int i = 0; i < dropItems.size(); i++)
	{
		ItemTable itemTable = *dropItems[i];

		if (itemTable.rate * 10000 < random(0.0f, 9999.0f)) {
			continue;
		}

		for (int j = 0; j < itemTable.number; j++)
		{
			Item* item = new Item();
			item->Init({ itemTable.path })
				->SetPosition(this->GetX() + random(-16.0f, 16.0f), this->GetY() + random(-16.0f, 16.0f))
				->SetTrigger(true)
				->SetId(itemTable.id)
				->SetActive(true);
			gameObjects.push_back(item);
		}
	}
	return this;
}