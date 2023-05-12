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

	MainCharacter* mainCharacter;

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetId() == "MainCharacter")
		{
			mainCharacter = (MainCharacter*)gameObjects[i];
			break;
		}
	}
	if (mainCharacter->GetX() + mainCharacter->GetWidth() < GetX() || mainCharacter->GetX() > GetX() + GetWidth())
	{
		return;
	}

	if (mainCharacter->GetY() + mainCharacter->GetHeight() < GetY() || mainCharacter->GetY() > GetY() + GetHeight())
	{
		return;
	}
	Attack(mainCharacter);
}

void Enemy::Attack(GameObject* gameObject)
{
	if (dynamic_cast<MainCharacter*>(gameObject))
	{
		dynamic_cast<MainCharacter*>(gameObject)->OnAttacked(this);
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

		if (useTool == "wood_sword") {
			damage = 2;
		}

		if (useTool == "stone_sword") {
			damage = 3;
		}

		if (useTool == "iron_sword") {
			damage = 4;
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