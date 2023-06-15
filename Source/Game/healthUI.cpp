#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "gameObject.h"
#include "healthUI.h"
#include "MainCharacter.h"
#include <string>
#include "tool.h"
#include "config.h"

using namespace game_framework;

HealthUI* HealthUI::Init()
{
	GameObject::Init({
		"resources/health_0_ui.bmp" ,
		"resources/health_1_ui.bmp" ,
		"resources/health_2_ui.bmp" ,
		"resources/health_3_ui.bmp" ,
		"resources/health_4_ui.bmp" ,
		"resources/health_5_ui.bmp" ,
		"resources/health_6_ui.bmp" ,
		"resources/health_7_ui.bmp" ,
		"resources/health_8_ui.bmp" ,
		"resources/health_9_ui.bmp" ,
		"resources/health_10_ui.bmp"
		});

	return this;
}

void HealthUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
	int hpRate = (int)(mainCharacter->GetHp() / 10.0f) + 1;
	if (hpRate > 10) {
		hpRate = 10;
	}
	else if (hpRate < 0) {
		hpRate = 0;
	}
	bitmap.SetFrameIndexOfBitmap(hpRate);
}

void HealthUI::Render(GameObject* mainObject)
{
	GameObject::Render(mainObject);
	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 16, "Arial Black", RGB(255, 255, 255));
	if (mainCharacter->GetHp() < 100) {
		CTextDraw::Print(pDC, SIZE_X / 2 - (int)GetWidth() / 2 + 32, 6, std::to_string((int)mainCharacter->GetHp()) + " / 100");
	}
	else if (mainCharacter->GetHp() < 10) {
		CTextDraw::Print(pDC, SIZE_X / 2 - (int)GetWidth() / 2 + 28, 6, std::to_string((int)mainCharacter->GetHp()) + " / 100");
	}
	else {
		CTextDraw::Print(pDC, SIZE_X / 2 - (int)GetWidth() / 2 + 24, 6, std::to_string((int)mainCharacter->GetHp()) + " / 100");
	}
	CDDraw::ReleaseBackCDC();

}



HealthUI* HealthUI::SetMainCharacter(MainCharacter* mainCharacter) {
	this->mainCharacter = mainCharacter;

	return this;
}
