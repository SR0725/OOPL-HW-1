#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "nightUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

NightUI* NightUI::Init()
{
	GameObject::Init({
		"resources/dark_1.bmp" ,
		"resources/dark_2.bmp" ,
		"resources/dark_3.bmp" ,
		"resources/dark_4.bmp" ,
		"resources/dark_5.bmp" ,
		"resources/dark_6.bmp" ,
		"resources/dark_7.bmp" ,
		"resources/dark_8.bmp" ,
		"resources/dark_9.bmp" ,
		"resources/dark_10.bmp" ,
		"resources/dark_11.bmp" ,
		"resources/dark_12.bmp" ,
		"resources/empty.bmp" ,
		});

	return this;
}

void NightUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
}

void NightUI::Render(GameObject* mainObject, float time)
{
	float dayTime = time - ((int)(time / DAY_TIME))* DAY_TIME;

	if (dayTime > DAY_TIME / 3 * 2) {
		float nightTime = dayTime - DAY_TIME / 3 * 2;
		int frameIndex = (int)(11 - nightTime * 3);

		if (frameIndex < 0) {
			frameIndex = 0;
		}
		bitmap.SetFrameIndexOfBitmap(frameIndex);
	}
	else {
		int frameIndex = (int)(dayTime * 6);

		if (frameIndex > 12) {
			frameIndex = 12;
		}
		bitmap.SetFrameIndexOfBitmap(frameIndex);
	}

	GameObject::Render(mainObject);
}



NightUI* NightUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
