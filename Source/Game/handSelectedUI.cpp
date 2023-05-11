#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "handSelectedUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

HandSelectedUI* HandSelectedUI::Init(vector<string> filename)
{
	GameObject::Init(filename);

	return this;
}

void HandSelectedUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	GameObject::SetPosition((SIZE_X / 2.0f) - (52 * 3.5f) + (float)this->mainCharacter->GetMainHandSelectedIndex() * 52 - 4.0f, SIZE_Y - 76.0f);

	GameObject::OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
}


HandSelectedUI* HandSelectedUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
