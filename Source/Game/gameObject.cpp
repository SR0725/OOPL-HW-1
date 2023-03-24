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

void GameObject::Init(vector<string> filename, int _x, int _y, float _speed = 0)
{
    bitmap.LoadBitmapByString(filename, RGB(255, 255, 255));
    x = _x;
    y = _y;
    speed = _speed;
}

void GameObject::SetActive(bool _active = true)
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

void GameObject::Render()
{
    bitmap.SetTopLeft(x, y);
    bitmap.ShowBitmap();
}
