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
#include "hungryUI.h"
#include "gameOverUI.h"
#include "thirstyUI.h"
#include "clockUI.h"

using namespace game_framework;

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
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
	BackGround* background = new BackGround();
	background->Init({ "resources/terrian.bmp" })->SetActive(true);

	MainCharacter* character = new MainCharacter();
	character
		->SetTerrian(terrian)
		->Init({ "resources/player_10.bmp","resources/player_11.bmp","resources/player_00.bmp","resources/player_01.bmp" })
		->SetHp(100)
		->SetPosition(256, 256)
		->SetSpeed(2.0f)
		->SetCollider(true)
		->SetTrigger(true)
		->SetActive(true)
		->SetId("MainCharacter");

	gameObjects.push_back(background);
	gameObjects.push_back(character);


}

void CGameStateRun::MountedTerrian()
{
	for (int i = 0; i < 60; i++)
	{
		// random position
		int x = rand() % 20 + 1;
		int y = rand() % 20 + 1;
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
		else if (randValue < 50)
			blockType = 2; // 10% 小樹
		else if (randValue < 70)
			blockType = 3; // 20% 石頭
		else if (randValue < 80)
			blockType = 4; // 10% 煤炭
		else if (randValue < 90)
			blockType = 9; // 10% 沙子
		else if (randValue < 100)
			blockType = 5; // 10% 鐵礦
		// create block
		terrian->SetBlock(x * 48.0f, y * 48.0f, blockType);
	}
	// water
	for (int i = 0; i < 3; i++)
	{
		// random position
		int x = rand() % 21;
		int y = rand() % 21;
		if (terrian->IsBlock(x * 48.0f, y * 48.0f))
		{
			i--;
			continue;
		}
		const int waterBlockType = 8;
		// create block
		terrian->SetBlock(x * 48.0f, y * 48.0f, waterBlockType);
	}
}

void CGameStateRun::MountedUIObject()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);



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


	HungryUI* hungryUI = new HungryUI();
	hungryUI
		->Init()
		->SetMainCharacter(character)
		->SetPosition(SIZE_X / 2 - 108, 24)
		->SetActive(true)
		->SetUI(true);

	ThirstyUI* thirstyUI = new ThirstyUI();
	thirstyUI
		->Init()
		->SetMainCharacter(character)
		->SetPosition(SIZE_X / 2 + 60, 24)
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
	uiObjects.push_back(hungryUI);
	uiObjects.push_back(thirstyUI);
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
				MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

				for (int i = 0; i < day; i++)
				{
					float randWeight = (rand() % 2) == 0 ? 1.0f : -1.0f;
					float x = character->GetX() + randWeight * (float)(rand() % 128 + 96);
					randWeight = (rand() % 2) == 0 ? 1.0f : -1.0f;
					float y = character->GetY() + randWeight * (float)(rand() % 128 + 96);
					Enemy* testEnemy = new Enemy();
					testEnemy
						->SetDropItems(
							new vector<ItemTable*>({
									new ItemTable("raw_meat", "resources/raw_meat.bmp", 0.5, 1),
								}))
								->Init({ "resources/enemy_10.bmp","resources/enemy_11.bmp","resources/enemy_00.bmp","resources/enemy_01.bmp" })
						->SetHp(10)
						->SetAttack(10)
						->SetDefense(10)
						->SetPosition(x, y)
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
	float dayTime = time - ((int)(time / DAY_TIME)) * DAY_TIME;
	day = (int)(time / DAY_TIME) + 1;

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	}
	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		(*uiObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	}

	NightGenaratedMonster();

	// check if main character is dead
	if (dynamic_cast<MainCharacter*>(gameObjects[1])->GetHp() <= 0 && !gameover)
	{
		gameover = true;
		// show game over ui
		GameOverUI* gameOverUI = new GameOverUI();
		gameOverUI
			->Init(time, day)
			->SetPosition(0, 0)
			->SetActive(true)
			->SetUI(true);

		uiObjects.push_back(gameOverUI);
	}

	if (invincible) {
		MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
		character->SetHp(100);
		character->SetHungry(100);
		character->SetThirsty(100);
		character->attack = 100000;
	}
	else {
		MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

		character->attack = 1;
	}
}

void CGameStateRun::OnShow()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		// skip main character
		if (i == 1) {
			continue;
		}
		(*gameObjects[i]).Render(character);
	}
	// render main character
	(*gameObjects[1]).Render(character);

	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		if (dynamic_cast<InventoryUI*>(uiObjects[i]))
		{
			dynamic_cast<InventoryUI*>(uiObjects[i])->Render(character);
		}
		else if (dynamic_cast<CraftItem*>(uiObjects[i]))
		{
			dynamic_cast<CraftItem*>(uiObjects[i])->Render(character);
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
		else if (dynamic_cast<GameOverUI*>(uiObjects[i]))
		{
			dynamic_cast<GameOverUI*>(uiObjects[i])->Render(character);
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

	// i -> invincible mode
	if (nChar == 0x49)
	{
		invincible = !invincible;
	}
	// o -> regenerate terrian
	if (nChar == 0x4F)
	{
		MountedTerrian();
	}
	// P -> kill all enemy
	if (nChar == 0x50)
	{
		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			if (dynamic_cast<Enemy*>(gameObjects[i]))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(gameObjects[i]);
				enemy->SetHp(0);
			}
		}
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
		GameObject* obj = uiObjects[i];
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
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	int relativeMouseX = mouseX + (int)character->GetX() - SIZE_X / 2;
	int relativeMouseY = mouseY + (int)character->GetY() - SIZE_Y / 2;
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		GameObject* obj = gameObjects[i];
		if (obj->GetX() + obj->GetWidth() - 24.0f < relativeMouseX || obj->GetX() - 24.0f > relativeMouseX)
		{
			continue;
		}

		if (obj->GetY() + obj->GetHeight() - 24.0f < relativeMouseY || obj->GetY() - 24.0f > relativeMouseY)
		{
			continue;
		}

		if (dynamic_cast<Block*>(obj))
		{
			dynamic_cast<Block*>(obj)->OnClick(gameObjects);
		}
	}
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), '1'), pressedKeys.end());
}

void CGameStateRun::debug_text()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 24, "Arial Black", RGB(255, 255, 255));
	CTextDraw::Print(pDC, SIZE_X - 128, 24, "DAY " + std::to_string(day));
	if (invincible) {
		CTextDraw::Print(pDC, 16, 16, "Invincible Mode");
	}
	CDDraw::ReleaseBackCDC();
}