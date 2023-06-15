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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	load_background();
}

void CGameStateOver::OnShow()
{
	background.ShowBitmap();
}

void CGameStateOver::load_background()
{
	background.LoadBitmapByString({ "resources/game_end_background.bmp" });
	background.SetTopLeft(0, 0);
}
