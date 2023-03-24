#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <algorithm>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit()
{
	background.Init({"resources/terrian.bmp"}, 0, 0, 1.0f);
	character.Init({"resources/player_0.bmp"}, 0, 0, 1.0f);
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // ���ʹC������
{
	background.OnUpdate(pressedKeys);
	character.OnUpdate(pressedKeys);
}

void CGameStateRun::OnShow()
{
	background.Render(&character);
	character.Render(&character);
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
	if (nChar == 0x57)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'W'), pressedKeys.end());
	}
	// s
	if (nChar == 0x53)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'S'), pressedKeys.end());

	}
	// a
	if (nChar == 0x41)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'A'), pressedKeys.end());

	}
	// d
	if (nChar == 0x44)
	{
		pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), 'D'), pressedKeys.end());

	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::debug_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	/* Print info */
	CTextDraw::Print(pDC, 0, 0, "awddwwd");

	CDDraw::ReleaseBackCDC();
}