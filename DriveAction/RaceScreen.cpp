#include "RaceScreen.h"
#include "Utility.h"
#include "DxLib.h"
/// <summary>
/// 描画した画像を保存する
/// </summary>
RaceScreen::RaceScreen()
{
    DeleteGraph(screen);
    screen = -1;
}

RaceScreen::~RaceScreen()
{
    DeleteGraph(screen);
    screen = -1;
}

/// <summary>
/// 描画している画像を更新
/// </summary>
void RaceScreen::ScreenUpdate()
{
    DeleteGraph(screen);
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

void RaceScreen::Draw()
{
   DrawGraph(0, 0, screen, false);
}
