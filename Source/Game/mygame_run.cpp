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
#include "craftItem.h"
#include "MainCharacter.h"
#include "BackGround.h"
#include "MainCharacter.h"
#include "Block.h"
#include "InventoryUI.h"
#include "Enemy.h"
#include "tool.h"

using namespace game_framework;

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit()
{
	MountedGameObject();
	MountedTerrian();
	MountedUIObject();
}

void CGameStateRun::MountedGameObject()
{
	BackGround* background = new BackGround();
	background->Init({ "resources/terrian.bmp" })->SetActive(true);

	MainCharacter* character = new MainCharacter();
	character->Init({ "resources/player_0.bmp" })
		->SetPosition(256, 256)
		->SetSpeed(4.0f)
		->SetCollider(true)
		->SetTrigger(true)
		->SetActive(true)
		->SetId("MainCharacter");


	gameObjects.push_back(background);
	gameObjects.push_back(character);


	for (int i = 0; i < 1; i++) {
		Enemy* testEnemy = new Enemy();
		testEnemy
			->Init({ "resources/enemy.bmp" })
			->SetHp(100)
			->SetAttack(10)
			->SetDefense(10)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetSpeed(1.0f)
			->SetCollider(true)
			->SetTrigger(true)
			->SetActive(true)
			->SetId("Enemy");
		gameObjects.push_back(testEnemy);
	}

}

void CGameStateRun::MountedTerrian()
{
	// 建立大樹
	for (int i = 0; i < 24; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/tree_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/log.bmp", 1, 4),
					})
					)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetCollider(true)
			->SetId("tree_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	// 建立小樹
	for (int i = 0; i < 8; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/tree_apple_small_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/log.bmp", 1, 2),
					})
					)
			->SetPosition((float)floor(random(0, 1000)), (float)floor((int)random(0, 1000)))
			->SetCollider(true)
			->SetId("tree_apple_small_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	// 建立石頭
	for (int i = 0; i < 8; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/stone_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/stone.bmp", 1, 4),
					})
					)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetCollider(true)
			->SetId("stone_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	// 建立煤炭
	for (int i = 0; i < 4; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/coal_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/stone.bmp", 1, 2),
					new ItemTable("log", "resources/coal.bmp", 1, 4),
					})
					)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetCollider(true)
			->SetId("coal_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	// 建立鐵礦
	for (int i = 0; i < 4; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/iron_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/iron.bmp", 1, 4),
					})
					)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetCollider(true)
			->SetId("iron_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	// 建立銀礦
	for (int i = 0; i < 2; i++)
	{
		Block* tempTree = new Block();
		tempTree
			->Init({ "resources/slive_block.bmp" })
			->SetDropItems(
				vector<ItemTable*>({
					new ItemTable("log", "resources/slive.bmp", 1, 4),
					})
					)
			->SetPosition((float)floor(random(0, 1024)), (float)floor((int)random(0, 1024)))
			->SetCollider(true)
			->SetId("slive_block")
			->SetActive(true);
		gameObjects.push_back(tempTree);
	}
}

void CGameStateRun::MountedUIObject()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	InventoriesUI* inventoryUI = new InventoriesUI();
	inventoryUI->Init(character, uiObjects);

	CraftItem* craftItem_craftTable = new CraftItem();

	craftItem_craftTable
		->Init({ "resources/craft_craft_table.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("log", "resources/log.bmp", 1, 10),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("test", "resources/test.bmp", 1, 1)
				})
		)
		->SetPosition(424, 100)
		->SetActive(true)
		->SetUI(true);
	uiObjects.push_back(craftItem_craftTable);

	uiObjects.push_back(inventoryUI);
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()
{
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).OnUpdate(pressedKeys, gameObjects);
	}
	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		(*uiObjects[i]).OnUpdate(pressedKeys, uiObjects);
	}
}

void CGameStateRun::OnShow()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).Render(character);
	}
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
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), '1'), pressedKeys.end());
}

void CGameStateRun::debug_text()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);

	CDC* pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 16, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 2, 2, "object numbers: " + std::to_string(gameObjects.size()));
	CTextDraw::Print(pDC, 2, 18, "action: " + pressedKeys);
	CTextDraw::Print(pDC, 2, 34, "x: " + std::to_string(character->GetX()));
	CTextDraw::Print(pDC, 2, 50, "y: " + std::to_string(character->GetY()));
	CTextDraw::Print(pDC, 2, 66, "mouseX: " + std::to_string(mouseX));
	CTextDraw::Print(pDC, 2, 82, "mouseY: " + std::to_string(mouseY));

	CDDraw::ReleaseBackCDC();
}