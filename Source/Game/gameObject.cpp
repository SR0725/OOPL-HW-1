#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "gameObject.h"
#include <string>
#include "config.h"

using namespace game_framework;

GameObject::GameObject()
{
    x = 0;
    y = 0;
    motionX = 0;
    motionY = 0;
    speed = 0;
    isUI = false;
    isCollider = false;
    isTrigger = false;
    active = false;
    id = "";
}

GameObject* GameObject::Init(vector<string> _filename)
{
    this->filename = _filename;
    bitmap.LoadBitmapByString(_filename, RGB(255, 255, 255));
	return this;
}

void GameObject::Destroy(vector<GameObject *> &gameObjects)
{
    bitmap.UnshowBitmap();
    for (unsigned int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i] == this)
        {
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}

GameObject* GameObject::SetUI(bool _isUI)
{
    isUI = _isUI;
    return this;
}

GameObject* GameObject::SetCollider(bool _isCollider)
{
    isCollider = _isCollider;
    return this;
}

GameObject* GameObject::SetTrigger(bool _isTrigger)
{
    isTrigger = _isTrigger;
    return this;
}

GameObject* GameObject::SetActive(bool _active)
{
    active = _active;
    if (active)
        bitmap.ShowBitmap();
    return this;
}

GameObject* GameObject::SetSpeed(float _speed)
{
    speed = _speed;
    return this;
}

GameObject* GameObject::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	return this;
}

GameObject* GameObject::SetX(float _x)
{
    x = _x;
    return this;
}

GameObject* GameObject::SetY(float _y)
{
    y = _y;
    return this;
}

GameObject* GameObject::SetId(string _id)
{
    id = _id;
    return this;
}


string GameObject::GetId()
{
    return id;
}

void GameObject::GoTop()
{
    motionY = -speed;
}

void GameObject::GoBottom()
{
    motionY = speed;
}

void GameObject::GoRight()
{
    motionX = speed;
}

void GameObject::GoLeft()
{
    motionX = -speed;
}

float GameObject::GetX()
{
    return x;
}

float GameObject::GetY()
{
    return y;
}


float GameObject::GetWidth()
{
    return float(bitmap.GetWidth());
}

float GameObject::GetHeight()
{
    return float(bitmap.GetHeight());
}

bool GameObject::GetIsCollider()
{
    return isCollider;
}

bool GameObject::GetIsTrigger()
{
    return isTrigger;
}

vector<string> game_framework::GameObject::GetFilename()
{
    return filename;
}

bool GameObject::isCollideWith(GameObject *obj)
{
    if (!isCollider || !obj->GetIsCollider())
    {
        return false;
    }

    if (x + bitmap.GetWidth() < obj->x || x > obj->x + obj->bitmap.GetWidth())
    {
        return false;
    }

    if (y + bitmap.GetHeight() < obj->y || y > obj->y + obj->bitmap.GetHeight())
    {
        return false;
    }

    return true;
}

bool GameObject::isTriggerWith(GameObject *obj)
{
    if (!isTrigger || !obj->GetIsTrigger())
    {
        return false;
    }

    if (x + bitmap.GetWidth() < obj->x || x > obj->x + obj->bitmap.GetWidth())
    {
        return false;
    }

    if (y + bitmap.GetHeight() < obj->y || y > obj->y + obj->bitmap.GetHeight())
    {
        return false;
    }

    return true;
}



void GameObject::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
    x += motionX;
    y += motionY;
}

void GameObject::OnClick(vector<GameObject*>& gameObjects)
{
}

void GameObject::Render(GameObject *mainObject)
{
    if (!active)
    {
        return;
    }
    bitmap.ShowBitmap();
    if (isUI)
    {
        bitmap.SetTopLeft(int(x), int(y));
        return;
    }
    float renderX = SIZE_X / 2.0f - mainObject->GetX() - mainObject->GetWidth() / 2.0f + x;
    float renderY = SIZE_Y / 2.0f - mainObject->GetY() - mainObject->GetHeight() / 2.0f + y;
    bitmap.SetTopLeft(int(renderX), int(renderY));
}

