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

InventoryBox::InventoryBox()
{
}

GameObject::GameObject()
{
}

void GameObject::Init(vector<string> _filename, float _x, float _y, float _speed)
{
    bitmap.LoadBitmapByString(_filename, RGB(255, 255, 255));
    x = _x;
    y = _y;
    speed = _speed;
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

void GameObject::GoTop()
{
    y -= speed;
}

void GameObject::GoBottom()
{
    y += speed;
}

void GameObject::GoRight()
{
    x += speed;
}

void GameObject::GoLeft()
{
    x -= speed;
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
    return float(bitmap.Width());
}

float GameObject::GetHeight()
{
    return float(bitmap.Height());
}

void GameObject::onKeyDown(string isKeyPressed, string isKeyDown, string isKeyReleased)
{
    if (isKeyPressed == "W")
    {
        GoTop();
    }
    else if (isKeyPressed == "S")
    {
        GoBottom();
    }
    else if (isKeyPressed == "A")
    {
        GoLeft();
    }
    else if (isKeyPressed == "D")
    {
        GoRight();
    }
}

bool GameObject::GetIsCollider()
{
    return isCollider;
}

bool GameObject::isCollideWith(GameObject *obj)
{
    if (!isCollider || !obj->GetIsCollider())
    {
        return false;
    }

    if (x + bitmap.Width() < obj->x || x > obj->x + obj->bitmap.Width())
    {
        return false;
    }

    if (y + bitmap.Height() < obj->y || y > obj->y + obj->bitmap.Height())
    {
        return false;
    }

    return true;
}

void GameObject::Render(GameObject *mainObject)
{
    float renderX = mainObject->GetX() + 320.0f - mainObject->GetWidth() / 2.0f + x;
    float renderY = mainObject->GetY() + 240.0f - mainObject->GetHeight() / 2.0f + y;
    bitmap.SetTopLeft(int(renderX), int(renderY));
    bitmap.ShowBitmap();
}
