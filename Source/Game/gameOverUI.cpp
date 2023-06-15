#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "gameOverUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

GameOverUI* GameOverUI::Init(float liveTime, int liveDay)
{
	this->time = liveTime;
	this->day = liveDay;

	GameObject::Init({
		"resources/game_end_background.bmp" ,
		});

	return this;
}

void GameOverUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{

}

void GameOverUI::Render(GameObject* mainObject)
{
	GameObject::Render(mainObject);


	CDC* pDC = CDDraw::GetBackCDC();
	// Day
	CTextDraw::ChangeFontLog(pDC, 48, "Arial Black", RGB(114, 44, 42));

	if (day >= 10 && day < 100) {
		CTextDraw::Print(pDC, 310 - 36, 152, std::to_string(day));
	}
	else if (day >= 100) {
		CTextDraw::Print(pDC, 310 - 72, 152, std::to_string(day));
	}
	else {
		CTextDraw::Print(pDC, 310, 152, std::to_string(day));
	}

	int hour = (int)time / 3600;
	int minute = ((int)time % 3600) / 60;
	int second = ((int)time % 3600) % 60;

	// Time
	CTextDraw::ChangeFontLog(pDC, 38, "Arial Black", RGB(114, 44, 42));
	CTextDraw::Print(pDC, 310, 232, std::to_string(hour) + " : " + std::to_string(minute) + " : " + std::to_string(second));

	CDDraw::ReleaseBackCDC();
}