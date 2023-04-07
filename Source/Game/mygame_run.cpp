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
#include "Tree.h"
#include "../Library/tool.h"

using namespace game_framework;

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit()
{
	gameObjects.push_back(&background);
	gameObjects.push_back(&character);
	background.Init({"resources/terrian.bmp"}, 0, 0, 1.0f);
	background.SetActive(true);

	character.Init({"resources/player_0.bmp"}, 0, 0, 4.0f);
	character.SetCollider(true);
	character.SetTrigger(true);
	character.SetActive(true);

	inventoryUI.Init(&character, gameObjects);

	tree.Init({"resources/tree.bmp"}, 16 * 16, 16 * 16, 1.0f);

	for (int i = 0; i < 64; i++)
	{
		Tree *tempTree = new Tree();
		tempTree->Init({"resources/tree.bmp"}, (float)ceil(random(0, 1024)), (float)ceil((int)random(0, 1024)), 1.0f);
		tempTree->SetCollider(true);
		tempTree->SetId("tree");
		tempTree->SetActive(true);
		gameObjects.push_back(tempTree);
	}

	gameObjects.push_back(&inventoryUI);
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
}

void CGameStateRun::OnShow()
{
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		(*gameObjects[i]).Render(&character);
	}
	debug_text();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57)
	{
		pressedKeys.append("W");
	}
	// s
	if (nChar == 0x53)
	{
		pressedKeys.append("S");
	}
	// a
	if (nChar == 0x41)
	{
		pressedKeys.append("A");
	}
	// d
	if (nChar == 0x44)
	{
		pressedKeys.append("D");
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
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.append("0");
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
	pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), '0'), pressedKeys.end());
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
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
	CDC *pDC = CDDraw::GetBackCDC();
	CFont *fp;
	CTextDraw::ChangeFontLog(pDC, fp, 16, "", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 2, 2, "object numbers: " + std::to_string(gameObjects.size()));
	CTextDraw::Print(pDC, 2, 18, "action: " + pressedKeys);
	CTextDraw::Print(pDC, 2, 34, "x: " + std::to_string(character.GetX()));
	CTextDraw::Print(pDC, 2, 50, "y: " + std::to_string(character.GetY()));

	CDDraw::ReleaseBackCDC();
}