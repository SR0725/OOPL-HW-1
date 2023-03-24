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
	background.LoadBitmapByString({"resources/terrian.bmp"});
	background.SetTopLeft(character_x + 320 - character.Width() / 2, character_y + 240 - character.Height() / 2);

	character.Init({"resources/character.bmp"}, 0, 0, 1.0f);
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // ���ʹC������
{
	// WASD ����
	if (on_key_w_down)
	{
		character.GoTop();
	}
	if (on_key_s_down)
	{
		character.GoBottom();
	}
	if (on_key_a_down)
	{
		character.GoLeft();
	}
	if (on_key_d_down)
	{
		character.GoRight();
	}

	// // ��ɧP�_
	// if (character_x > 0)
	// {
	// 	character_x = 0;
	// }
	// if (character_x < -background.Width() + character.Width())
	// {
	// 	character_x = -background.Width() + character.Width();
	// }
	// if (character_y > 0)
	// {
	// 	character_y = 0;
	// }
	// if (character_y < -background.Height() + character.Height())
	// {
	// 	character_y = -background.Height() + character.Height();
	// }
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	background.SetTopLeft(character.GetX() + 320 - character.GetWidth() / 2, character.GetY + 240 - character.GetHeight() / 2);
	character.Render();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57)
	{
		on_key_w_down = true;
	}
	// s
	if (nChar == 0x53)
	{
		on_key_s_down = true;
	}
	// a
	if (nChar == 0x41)
	{
		on_key_a_down = true;
	}
	// d
	if (nChar == 0x44)
	{
		on_key_d_down = true;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// W
	if (nChar == 0x57)
	{
		on_key_w_down = false;
	}
	// s
	if (nChar == 0x53)
	{
		on_key_s_down = false;
	}
	// a
	if (nChar == 0x41)
	{
		on_key_a_down = false;
	}
	// d
	if (nChar == 0x44)
	{
		on_key_d_down = false;
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