#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "clockUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

ClockUI* ClockUI::Init()
{
	GameObject::Init({
		"resources/clock_ui_1.bmp" ,
		"resources/clock_ui_2.bmp" ,
		"resources/clock_ui_3.bmp" ,
		"resources/clock_ui_4.bmp" ,
		"resources/clock_ui_5.bmp" ,
		"resources/clock_ui_6.bmp" ,
		"resources/clock_ui_7.bmp" ,
		"resources/clock_ui_8.bmp" ,
		"resources/clock_ui_9.bmp" ,
		"resources/clock_ui_10.bmp" ,
		"resources/clock_ui_11.bmp" ,
		"resources/clock_ui_12.bmp" ,
		});

	return this;
}

void ClockUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
}

void ClockUI::Render(GameObject* mainObject, float time)
{
	float dayTime = time - ((int)(time / DAY_TIME)) * DAY_TIME;

	int frameIndex = (int)(12 * dayTime / DAY_TIME);

	if (frameIndex > 11) {
		frameIndex = 11;
	}
	bitmap.SetFrameIndexOfBitmap(frameIndex);

	GameObject::Render(mainObject);
}



ClockUI* ClockUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
