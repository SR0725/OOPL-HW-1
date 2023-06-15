#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "thirstyUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

ThirstyUI* ThirstyUI::Init()
{
	GameObject::Init({
		"resources/thirsty_0_ui.bmp" ,
		"resources/thirsty_1_ui.bmp" ,
		"resources/thirsty_2_ui.bmp" ,
		"resources/thirsty_3_ui.bmp" ,
		"resources/thirsty_4_ui.bmp" ,
		"resources/thirsty_5_ui.bmp" ,
		"resources/thirsty_6_ui.bmp" ,
		"resources/thirsty_7_ui.bmp" ,
		"resources/thirsty_8_ui.bmp" ,
		"resources/thirsty_9_ui.bmp" ,
		"resources/thirsty_10_ui.bmp" ,
		});

	return this;
}

void ThirstyUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	int thirstyRate = (int)(mainCharacter->GetThirsty() / 10.0f) + 1;
	if (thirstyRate > 10) {
		thirstyRate = 10;
	}
	else if (thirstyRate < 0) {
		thirstyRate = 0;
	}
	bitmap.SetFrameIndexOfBitmap(thirstyRate);
}

void ThirstyUI::Render(GameObject* mainObject)
{
	GameObject::Render(mainObject);
}



ThirstyUI* ThirstyUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
