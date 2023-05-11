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
#include "handSelectedUI.h"

using namespace game_framework;


CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit()
{
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
		->Init({ "resources/player_0.bmp" })
		->SetPosition(256, 256)
		->SetSpeed(4.0f)
		->SetCollider(true)
		->SetTrigger(true)
		->SetActive(true)
		->SetId("MainCharacter");


	gameObjects.push_back(background);
	gameObjects.push_back(character);


	for (int i = 0; i < 0; i++) {
		Enemy* testEnemy = new Enemy();
		testEnemy
			->Init({ "resources/enemy.bmp" })
			->SetHp(100)
			->SetAttack(10)
			->SetDefense(10)
			->SetPosition(0,0)
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
	for (int i = 0; i < 64; i++)
	{
		// random position
		int x = rand() % 21;
		int y = rand() % 21;
		if (terrian->IsBlock(x*48.0f, y*48.0f)) {
			i--;
			continue;
		}
		// random block
		int randValue = rand() % 100;
		int blockType = 0;
		if (randValue < 40) blockType = 1; // 40% 大樹
		else if (randValue < 60) blockType = 2; // 20% 小樹
		else if (randValue < 80) blockType = 3; // 20% 石頭
		else if (randValue < 90) blockType = 4; // 10% 煤炭
		else if (randValue < 95) blockType = 5; // 5% 鐵礦
		else if (randValue < 100) blockType = 6; // 5% 銀礦
		// create block
		terrian->SetBlock(x * 48.0f, y * 48.0f, blockType);
	}
}

void CGameStateRun::MountedUIObject()
{
	MainCharacter* character = dynamic_cast<MainCharacter*>(gameObjects[1]);
	InventoriesUI* inventoryUI = new InventoriesUI();
	inventoryUI->Init(character, uiObjects);

	CraftItem* craftItem_craftTable = new CraftItem();
	CraftItem* craftItem_wood_axe = new CraftItem();
	CraftItem* craftItem_wood_pickaxe = new CraftItem();
	CraftItem* craftItem_wood_sword = new CraftItem();

	CraftItem* craftItem_stone_axe = new CraftItem();
	CraftItem* craftItem_stone_pickaxe = new CraftItem();
	CraftItem* craftItem_stone_sword = new CraftItem();

	CraftItem* craftItem_iron_axe = new CraftItem();
	CraftItem* craftItem_iron_pickaxe = new CraftItem();
	CraftItem* craftItem_iron_sword = new CraftItem();

	craftItem_craftTable
		->Init({ "resources/craft_craft_table.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("log", "resources/log.bmp", 1, 6),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("craft_table", "resources/craft_table.bmp", 1, 1)
				})
		)
		->SetPosition(424, 148)
		->SetActive(true)
		->SetUI(true);

	// wood tool
	craftItem_wood_axe
		->SetOnlyTable(true)
		->Init({ "resources/wood_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("log", "resources/log.bmp", 1, 5),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("wood_axe", "resources/wood_axe.bmp", 1, 1)
				})
		)
		->SetPosition(164, 44)
		->SetActive(true)
		->SetUI(true);



	craftItem_wood_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/wood_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("log", "resources/log.bmp", 1, 5),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("wood_pickaxe", "resources/wood_pickaxe.bmp", 1, 1)
				})
		)
		->SetPosition(216, 44)
		->SetActive(true)
		->SetUI(true);

	craftItem_wood_sword
		->SetOnlyTable(true)
		->Init({ "resources/wood_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("log", "resources/log.bmp", 1, 5),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("wood_sword", "resources/wood_sword.bmp", 1, 1)
				})
		)
		->SetPosition(268, 44)
		->SetActive(true)
		->SetUI(true);


	// stone tool
	craftItem_stone_axe
		->SetOnlyTable(true)
		->Init({ "resources/stone_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("stone", "resources/stone.bmp", 1, 5),
				new ItemTable("wood_axe", "resources/wood_axe.bmp", 1, 1),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("stone_axe", "resources/stone_axe.bmp", 1, 1)
				})
		)
		->SetPosition(320, 44)
		->SetActive(true)
		->SetUI(true);



	craftItem_stone_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/stone_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("stone", "resources/stone.bmp", 1, 5),
				new ItemTable("wood_pickaxe", "resources/wood_pickaxe.bmp", 1, 1),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("stone_pickaxe", "resources/stone_pickaxe.bmp", 1, 1)
				})
		)
		->SetPosition(372, 44)
		->SetActive(true)
		->SetUI(true);

	craftItem_stone_sword
		->SetOnlyTable(true)
		->Init({ "resources/stone_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("stone", "resources/stone.bmp", 1, 5),
				new ItemTable("wood_sword", "resources/wood_sword.bmp", 1, 1)
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("stone_sword", "resources/stone_sword.bmp", 1, 1)
				})
		)
		->SetPosition(424, 44)
		->SetActive(true)
		->SetUI(true);


	// iron tool
	craftItem_iron_axe
		->SetOnlyTable(true)
		->Init({ "resources/iron_axe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("iron", "resources/iron.bmp", 1, 5),
				new ItemTable("stone_axe", "resources/stone_axe.bmp", 1, 1),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("iron_axe", "resources/iron_axe.bmp", 1, 1)
				})
		)
		->SetPosition(164, 96)
		->SetActive(true)
		->SetUI(true);



	craftItem_iron_pickaxe
		->SetOnlyTable(true)
		->Init({ "resources/iron_pickaxe_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("iron", "resources/iron.bmp", 1, 5),
				new ItemTable("stone_pickaxe", "resources/stone_pickaxe.bmp", 1, 1),
				})
				)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("iron_pickaxe", "resources/iron_pickaxe.bmp", 1, 1)
				})
		)
		->SetPosition(216, 96)
		->SetActive(true)
		->SetUI(true);

	craftItem_iron_sword
		->SetOnlyTable(true)
		->Init({ "resources/iron_sword_craft.bmp" })
		->SetRawMaterials(
			vector<ItemTable*>({
				new ItemTable("iron", "resources/iron.bmp", 1, 5),
				new ItemTable("stone_sword", "resources/stone_sword.bmp", 1, 1)
				})
		)
		->SetProducts(
			vector<ItemTable*>({
				new ItemTable("iron_sword", "resources/iron_sword.bmp", 1, 1)
				})
		)
		->SetPosition(268, 96)
		->SetActive(true)
		->SetUI(true);


	HandSelectedUI* handSelected = new HandSelectedUI();
	handSelected
		->Init({ "resources/select_ui.bmp" })
		->SetMainCharacter(character)
		->SetActive(true)
		->SetUI(true);

	uiObjects.push_back(craftItem_craftTable);
	uiObjects.push_back(craftItem_wood_axe);
	uiObjects.push_back(craftItem_wood_pickaxe);
	uiObjects.push_back(craftItem_wood_sword);
	uiObjects.push_back(craftItem_stone_axe);
	uiObjects.push_back(craftItem_stone_pickaxe);
	uiObjects.push_back(craftItem_stone_sword);
	uiObjects.push_back(craftItem_iron_axe);
	uiObjects.push_back(craftItem_iron_pickaxe);
	uiObjects.push_back(craftItem_iron_sword);
	uiObjects.push_back(inventoryUI);
	uiObjects.push_back(handSelected);
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()
{
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
	}
	for (unsigned int i = 0; i < uiObjects.size(); i++)
	{
		(*uiObjects[i]).OnUpdate(pressedKeys, gameObjects, uiObjects, mouseX, mouseY);
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
	int relativeMouseX = mouseX + (int)character->GetX() - 320;
	int relativeMouseY = mouseY + (int)character->GetY() - 240;
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
	CTextDraw::ChangeFontLog(pDC, 16, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 2, 2, "object numbers: " + std::to_string(gameObjects.size()));
	CTextDraw::Print(pDC, 2, 18, "action: " + pressedKeys);
	CTextDraw::Print(pDC, 2, 34, "x: " + std::to_string(character->GetX()));
	CTextDraw::Print(pDC, 2, 50, "y: " + std::to_string(character->GetY()));
	CTextDraw::Print(pDC, 2, 66, "mouseX: " + std::to_string(mouseX));
	CTextDraw::Print(pDC, 2, 82, "mouseY: " + std::to_string(mouseY));

	CDDraw::ReleaseBackCDC();
}