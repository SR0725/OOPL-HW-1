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

HealthUI* HealthUI::Init()
{
	GameObject::Init({
		"resources/health_ui.bmp" ,
		});

	return this;
}

void HealthUI::OnUpdate(string pressedKeys, vector<GameObject*>& gameObjects, vector<GameObject*>& uiObjects, int mouseX, int mouseY)
{
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
