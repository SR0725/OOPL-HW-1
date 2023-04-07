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

void GameObject::Init(vector<string> _filename, float _x, float _y, float _speed)
{
    bitmap.LoadBitmapByString(_filename, RGB(255, 255, 255));
    x = _x;
    y = _y;
    speed = _speed;
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

void GameObject::SetUI(bool _isUI)
{
    isUI = _isUI;
}

void GameObject::SetCollider(bool _isCollider)
{
    isCollider = _isCollider;
}

void GameObject::SetTrigger(bool _isTrigger)
{
    isTrigger = _isTrigger;
}

void GameObject::SetActive(bool _active)
{
    active = _active;
    if (active)
        bitmap.ShowBitmap();
}

void GameObject::SetSpeed(float _speed)
{
    speed = _speed;
}

void GameObject::OnUpdate(string pressedKeys, vector<GameObject *> &gameObjects)
{
    x += motionX;
    y += motionY;
}

void GameObject::SetId(string _id)
{
    id = _id;
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

void GameObject::SetX(float _x)
{
    x = _x;
}

void GameObject::SetY(float _y)
{
    y = _y;
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
        bitmap.ShowBitmap();
        return;
    }
    float renderX = 320.0f - mainObject->GetX() - mainObject->GetWidth() / 2.0f + x;
    float renderY = 240.0f - mainObject->GetY() - mainObject->GetHeight() / 2.0f + y;
    bitmap.SetTopLeft(int(renderX), int(renderY));
}
