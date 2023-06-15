#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "hungryUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

HungryUI* HungryUI::Init()
{
	GameObject::Init({
		"resources/hungry_0_ui.bmp" ,
		"resources/hungry_1_ui.bmp" ,
		"resources/hungry_2_ui.bmp" ,
		"resources/hungry_3_ui.bmp" ,
		"resources/hungry_4_ui.bmp" ,
		"resources/hungry_5_ui.bmp" ,
		"resources/hungry_6_ui.bmp" ,
		"resources/hungry_7_ui.bmp" ,
		"resources/hungry_8_ui.bmp" ,
		"resources/hungry_9_ui.bmp" ,
		"resources/hungry_10_ui.bmp" ,
		});

	return this;
}

void HungryUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	int hungryRate = (int)(mainCharacter->GetHungry() / 10.0f) + 1;
	if (hungryRate > 10) {
		hungryRate = 10;
	}
	else if (hungryRate < 0) {
		hungryRate = 0;
	}
	bitmap.SetFrameIndexOfBitmap(hungryRate);
}

void HungryUI::Render(GameObject* mainObject)
{
	GameObject::Render(mainObject);
}



HungryUI* HungryUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
