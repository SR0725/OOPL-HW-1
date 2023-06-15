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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	ShowInitProgress(0, "Start Initialize...");
	Sleep(200);

	load_background();
	CAudio::Instance()->Load(0, "resources/background.wav");
	CAudio::Instance()->Load(1001, "resources/footstep_1.wav");
	CAudio::Instance()->Load(1002, "resources/footstep_2.wav");
	CAudio::Instance()->Load(1003, "resources/footstep_3.wav");
	CAudio::Instance()->Load(1004, "resources/footstep_4.wav");
	CAudio::Instance()->Load(1005, "resources/footstep_5.wav");

	CAudio::Instance()->Load(1011, "resources/hit_block_1.wav");
	CAudio::Instance()->Load(1012, "resources/hit_block_2.wav");
	CAudio::Instance()->Load(1013, "resources/hit_block_3.wav");
	CAudio::Instance()->Load(1014, "resources/hit_block_4.wav");
	CAudio::Instance()->Load(1015, "resources/hit_block_5.wav");

	CAudio::Instance()->Load(2001, "resources/burn.wav");
	CAudio::Instance()->Load(2002, "resources/getItem.wav");
	CAudio::Instance()->Load(2003, "resources/onhit.wav");

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	CAudio::Instance()->Play(0, true);



}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
}

void CGameStateInit::load_background()
{
	background.LoadBitmapByString({"resources/game_start_background.bmp"});
	background.SetTopLeft(0, 0);
}
