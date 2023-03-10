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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({"resources/terrian.bmp"});

	character.LoadBitmapByString({"resources/player_0.bmp"}, RGB(255, 255, 255));
	character_x = 0;
	character_y = 0;
	character.SetTopLeft(320 - character.Width() / 2, 240 - character.Height() / 2);
	background.SetTopLeft(character_x + 320 - character.Width() / 2, character_y + 240 - character.Height() / 2);

	// ui
	for (int i = 0; i < 10; i++)
	{
		ui_health[i].LoadBitmapByString({"resources/health_full.bmp", "resources/health_empty.bmp"}, RGB(255, 255, 255));
	}
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
	// WASD 移動
	if (on_key_w_down)
	{
		character_y += 10;
	}
	if (on_key_s_down)
	{
		character_y -= 10;
	}
	if (on_key_a_down)
	{
		character_x += 10;
	}
	if (on_key_d_down)
	{
		character_x -= 10;
	}

	// 邊界判斷
	if (character_x > 0)
	{
		character_x = 0;
	}
	if (character_x < -background.Width() + character.Width())
	{
		character_x = -background.Width() + character.Width();
	}
	if (character_y > 0)
	{
		character_y = 0;
	}
	if (character_y < -background.Height() + character.Height())
	{
		character_y = -background.Height() + character.Height();
	}
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	character.ShowBitmap();
	background.SetTopLeft(character_x + 320 - character.Width() / 2, character_y + 240 - character.Height() / 2);
	RenderUI();
}

void CGameStateRun::RenderUI()
{
	for (int i = 0; i < 10; i++)
	{
		ui_health[i].ShowBitmap();
		ui_health[i].SetTopLeft(i * (ui_health[i].Width() + 4), 0);
		if (character_health > i)
		{
			ui_health[i].SelectShowBitmap(0);
		}
		else
		{
			ui_health[i].SelectShowBitmap(1);
		}
	}
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}