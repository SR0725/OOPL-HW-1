#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	character.onUpdate(pressedKeys);
}

void CGameStateRun::OnShow()
{
	character.Render(&character);
	background.Render(&character);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57)
	{
		pressedKeys += "W";
	}
	// s
	if (nChar == 0x53)
	{
		pressedKeys += "S";
	}
	// a
	if (nChar == 0x41)
	{
		pressedKeys += "A";
	}
	// d
	if (nChar == 0x44)
	{
		pressedKeys += "D";
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57)
	{
		string::iterator it;
		for (it = pressedKeys.begin(); it < pressedKeys.end(); it++)
		{
			if (*it == 'W')
			{
				pressedKeys.erase(it);
				it--;
			}
		}
	}
	// s
	if (nChar == 0x53)
	{
		string::iterator it;
		for (it = pressedKeys.begin(); it < pressedKeys.end(); it++)
		{
			if (*it == 'S')
			{
				pressedKeys.erase(it);
				it--;
			}
		}
	}
	// a
	if (nChar == 0x41)
	{
		string::iterator it;
		for (it = pressedKeys.begin(); it < pressedKeys.end(); it++)
		{
			if (*it == 'A')
			{
				pressedKeys.erase(it);
				it--;
			}
		}
	}
	// d
	if (nChar == 0x44)
	{
		pressedKeysing::iterator it;
		for (it = pressedKeys.begin(); it < pressedKeys.end(); it++)
		{
			if (*it == 'D')
			{
				pressedKeys.erase(it);
				it--;
			}
		}
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