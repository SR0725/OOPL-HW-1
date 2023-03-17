#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
using namespace game_framework;

GameObject::GameObject(string bitmapSrc, int x, int y, int hungry, int health, int speed, int damage, bool isActive)
{
    this->bitmap.LoadBitmap(bitmapSrc.c_str(), RGB(255, 255, 255));
    this->x = x;
    this->y = y;
    this->hungry = hungry;
    this->health = health;
    this->speed = speed;
    this->damage = damage;
    this->isActive = isActive;
}

void GameObject::setActive(bool active)
{
    this->isActive = active;
}

void GameObject::goTop()
{
    this->y -= this->speed;
}

void GameObject::goDown()
{
    this->y += this->speed;
}

void GameObject::goLeft()
{
    this->x -= this->speed;
}

void GameObject::goRight()
{
    this->x += this->speed;
}

void GameObject::attack(GameObject *target)
{
    target->OnAttacken(this->damage);
}

void GameObject::OnAttacken(int damage)
{
    this->health -= damage;
    if (this->health <= 0)
    {
        this->die();
    }
}

void GameObject::addInventory(int id, int amount, string name, string description)
{
    for (int i = 0; i < 10; i++)
    {
        if (this->inventories[i].id == 0)
        {
            this->inventories[i].id = id;
            this->inventories[i].amount = amount;
            this->inventories[i].name = name;
            this->inventories[i].description = description;
            break;
        }
    }
}

InventoryBox *GameObject::getInventories()
{
    return this->inventories;
}

void GameObject::OnUpdate()
{
    if (this->isActive)
    {
        this->bitmap.SetTopLeft(this->x, this->y);
    }
}

void GameObject::die()
{
    this->isActive = false;
}
