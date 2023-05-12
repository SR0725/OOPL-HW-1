#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "craftTable.h"
#include "MainCharacter.h"
#include "BackGround.h"
#include "MainCharacter.h"
#include "Block.h"
#include "InventoryUI.h"
#include "Enemy.h"
#include "tool.h"
#include "handSelectedUI.h"
#include "config.h"
#include "nightUI.h"
#include "healthUI.h"
#include "clockUI.h"

using namespace game_framework;

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit()
{
	lastTimeClock = clock();
	time = 0;
	terrian = new Terrian(&gameObjects);
	MountedGameObject();
	MountedTerrian();
	MountedUIObject();
}

void CGameStateRun::MountedGameObject()
{
	BackGround *background = new BackGround();
	background->Init({"resources/terrian.bmp"})->SetActive(true);

	MainCharacter *character = new MainCharacter();
	character
			->SetTerrian(terrian)
			->Init({"resources/player_0.bmp"})
			->SetHp(100)
			->SetPosition(256, 256)
			->SetSpeed(1.5f)
			->SetCollider(true)
			->SetTrigger(true)
			->SetActive(true)
			->SetId("MainCharacter");

	gameObjects.push_back(background);
	gameObjects.push_back(character);
}

void CGameStateRun::MountedTerrian()
{
	for (int i = 0; i < 100; i++)
	{
		// random position
		int x = rand() % 21;
		int y = rand() % 21;
		if (terrian->IsBlock(x * 48.0f, y * 48.0f))
		{
			i--;
			continue;
		}
		// random block
		int randValue = rand() % 100;
		int blockType = 0;
		if (randValue < 40)
			blockType = 1; // 40% 大樹
		else if (randValue < 60)
			blockType = 2; // 20% 小樹
		else if (randValue < 80)
			blockType = 3; // 20% 石頭
		else if (randValue < 90)
			blockType = 4; // 10% 煤炭
		else if (randValue < 95)
			blockType = 5; // 5% 鐵礦
		else if (randValue < 100)
			blockType = 6; // 5% 銀礦
		// create block
		terrian->SetBlock(x * 48.0f, y * 48.0f, blockType);
	}
}

void CGameStateRun::MountedUIObject()
{
	MainCharacter *character = dynamic_cast<MainCharacter *>(gameObjects[1]);



	NightUI* nightUI = new NightUI();
	nightUI
		->Init()
		->SetMainCharacter(character)
		->SetPosition(0, 0)
		->SetActive(true)
		->SetUI(true);
	uiObjects.push_back(nightUI);


	InventoriesUI* inventoryUI = new InventoriesUI();
	inventoryUI->Init(character, uiObjects);

	CraftTable* craftTable = new CraftTable();
	craftTable->Init(uiObjects);

	HandSelectedUI* handSelected = new HandSelectedUI();
	handSelected
		->Init({ "resources/select_ui.bmp" })
		->SetMainCharacter(character)
		->SetActive(true)
		->SetUI(true);


	HealthUI* healthUI = new HealthUI();
	healthUI
		->Init()
		->SetMainCharacter(character)
		->SetPosition(SIZE_X / 2 - 64, 0)
		->SetActive(true)
		->SetUI(true);

	ClockUI* clockUI = new ClockUI();
	clockUI
		->Init()
		->SetMainCharacter(character)
		->SetPosition(SIZE_X / 2 - 64, 0)
		->SetActive(true)
		->SetUI(true);


	uiObjects.push_back(inventoryUI);
	uiObjects.push_back(craftTable);
	uiObjects.push_back(handSelected);
	uiObjects.push_back(healthUI);
	uiObjects.push_back(clockUI);
}

void CGameStateRun::NightGenaratedMonster()
{
	float dayTime = time - ((int)(time / DAY_TIME)) * DAY_TIME;

	if (dayTime > DAY_TIME / 3 * 2) {
		float nightTime = dayTime - DAY_TIME / 3 * 2;

		for (int i = 0; i < 6; i++)
		{

			if (nightTime > i * 12 && monsterState == i) {
				for (int i = 0; i < 6; i++)
				{
					Enemy* testEnemy = new Enemy();
					testEnemy
						->Init({ "resources/enemy.bmp" })
						->SetHp(10)
						->SetAttack(10)
						->SetDefense(10)
						->SetPosition((float)(rand() % 1000), (float)(rand() % 1000))
						->SetSpeed(1.0f)
						->SetCollider(true)
						->SetTrigger(true)
						->SetActive(true)
						->SetId("Enemy");
					gameObjects.push_back(testEnemy);
				}
				monsterState = i + 1;
			}
		}
	}
	else {
		monsterState = 0;
	}

}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()
{
	clock_t newTimeClock = clock();
	time += (float)(newTimeClock - lastTimeClock) / CLOCKS_PER_SEC;
	lastTimeClock = newTimeClock;

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	}
	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		(*uiObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	}

	NightGenaratedMonster();
}

void CGameStateRun::OnShow()
{
	MainCharacter *character = dynamic_cast<MainCharacter *>(gameObjects[1]);
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).Render(character);
	}
	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		if (dynamic_cast<InventoryUI *>(uiObjects[i]))
		{
			dynamic_cast<InventoryUI *>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<CraftItem *>(uiObjects[i]))
		{
			dynamic_cast<CraftItem *>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<CraftTable*>(uiObjects[i]))
		{
			dynamic_cast<CraftTable*>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<InventoriesUI*>(uiObjects[i]))
		{
			dynamic_cast<InventoriesUI*>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<NightUI*>(uiObjects[i]))
		{
			dynamic_cast<NightUI*>(uiObjects[i])->Render(character, time);
		}
		else if (dynamic_cast<HealthUI*>(uiObjects[i]))
		{
			dynamic_cast<HealthUI*>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<ClockUI*>(uiObjects[i]))
		{
			dynamic_cast<ClockUI*>(uiObjects[i])->Render(character, time);
		}
		else
		{
			uiObjects[i]->Render(character);
		}
	}
	debug_text();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57 || nChar == 0x26)
	{
		pressedKeys.append("W");
	}
	// s
	if (nChar == 0x53 || nChar == 0x28)
	{
		pressedKeys.append("S");
	}
	// a
	if (nChar == 0x41 || nChar == 0x25)
	{
		pressedKeys.append("A");
	}
	// d
	if (nChar == 0x44 || nChar == 0x27)
	{
		pressedKeys.append("D");
	}
	// e
	if (nChar == 0x45)
	{
		pressedKeys.append("E");
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	string::iterator it;
	// W
	if (nChar == 0x57 || nChar == 0x26)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'W'), pressedKeys.end());
	}
	// s
	if (nChar == 0x53 || nChar == 0x28)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'S'), pressedKeys.end());
	}
	// a
	if (nChar == 0x41 || nChar == 0x25)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'A'), pressedKeys.end());
	}
	// d
	if (nChar == 0x44 || nChar == 0x27)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'D'), pressedKeys.end());
	}
	// e
	if (nChar == 0x45)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'E'), pressedKeys.end());
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
	pressedKeys.append("0");

	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		GameObject *obj = uiObjects[i];
		if (obj->GetX() + obj->GetWidth() < mouseX || obj->GetX() > mouseX)
		{
			continue;
		}

		if (obj->GetY() + obj->GetHeight() < mouseY || obj->GetY() > mouseY)
		{
			continue;
		}

		obj->OnClick(gameObjects);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
{
	pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), '0'), pressedKeys.end());
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	mouseX = point.x;
	mouseY = point.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.append("1");
	MainCharacter *character = dynamic_cast<MainCharacter *>(gameObjects[1]);
	int relativeMouseX = mouseX + (int)character->GetX() - SIZE_X / 2;
	int relativeMouseY = mouseY + (int)character->GetY() - SIZE_Y / 2;
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		GameObject *obj = gameObjects[i];
		if (obj->GetX() + obj->GetWidth() - 24.0f < relativeMouseX || obj->GetX() - 24.0f > relativeMouseX)
		{
			continue;
		}

		if (obj->GetY() + obj->GetHeight() - 24.0f < relativeMouseY || obj->GetY() - 24.0f > relativeMouseY)
		{
			continue;
		}

		if (dynamic_cast<Block *>(obj))
		{
			dynamic_cast<Block *>(obj)->OnClick(gameObjects);
		}
	}
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), '1'), pressedKeys.end());
}

void CGameStateRun::debug_text()
{
	MainCharacter *character = dynamic_cast<MainCharacter *>(gameObjects[1]);

	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 16, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 2, 2, "object numbers: " + std::to_string(gameObjects.size()));
	CTextDraw::Print(pDC, 2, 18, "action: " + pressedKeys);
	CTextDraw::Print(pDC, 2, 34, "x: " + std::to_string(character->GetX()));
	CTextDraw::Print(pDC, 2, 50, "y: " + std::to_string(character->GetY()));
	CTextDraw::Print(pDC, 2, 66, "mouseX: " + std::to_string(mouseX));
	CTextDraw::Print(pDC, 2, 82, "mouseY: " + std::to_string(mouseY));
	CTextDraw::Print(pDC, 2, 98, "time: " + std::to_string(time));
	CTextDraw::Print(pDC, 2, 114, "hp: " + std::to_string(dynamic_cast<MainCharacter*>(gameObjects[1])->GetHp()));

	CDDraw::ReleaseBackCDC();
}