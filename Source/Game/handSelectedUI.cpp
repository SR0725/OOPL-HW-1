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

using namespace game_framework;

HandSelectedUI* HandSelectedUI::Init(vector<string> filename)
{
	GameObject::Init(filename);

	return this;
}

void HandSelectedUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	GameObject::SetPosition(162 + (float)this->mainCharacter->GetMainHandSelectedIndex() * 52, 404.0f);

	GameObject::OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
}


HandSelectedUI* HandSelectedUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
