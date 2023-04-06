#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
#include "MainCharacter.h"
#include "Tree.h"
#include "Item.h"
#include <string>
#include "../Library/tool.h"

using namespace game_framework;

Inventory::Inventory(string id, string name, string description, int amount)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->amount = amount;
}

Inventory::Inventory(string id, string name, string description)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->amount = 1;
}

void MainCharacter::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
    GameObject::OnUpdate(pressedKeys, gameObjects);
    OnAttack(pressedKeys, gameObjects);
    OnMove(pressedKeys, gameObjects);
}

void MainCharacter::OnMove(string pressedKeys, vector<GameObject *> &gameObjects)
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

        if (gameObjects[i]->isTriggerWith(this) && dynamic_cast<Item *>(gameObjects[i]))
        {
            OnGetItem(dynamic_cast<Item *>(gameObjects[i]), gameObjects);
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

void MainCharacter::OnGetItem(Item *item, vector<GameObject *> &gameObjects)
{
    if (item->GetId() == "log")
    {
        addItemToInventory(item);
        item->Destroy(gameObjects);
    }
}

void MainCharacter::OnAttack(string pressedKeys, vector<GameObject *> &gameObjects)
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

void MainCharacter::Attack(GameObject *gameObject)
{
    if (dynamic_cast<Tree *>(gameObject))
    {
        dynamic_cast<Tree *>(gameObject)->OnAttacked(*this);
    }
}

void MainCharacter::addItemToInventory(Item *item)
{
    for (unsigned int i = 0; i < inventories.size(); i++)
    {
        if (inventories[i].id == item->GetId())
        {
            inventories[i].amount++;
            return;
        }
    }

    inventories.push_back(Inventory(item->GetId(), item->GetId(), item->GetId()));
}
