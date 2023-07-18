#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
//普通の経過秒数
double Clock::gameTime;
Clock::Clock()
{
    // 現在のカウントを取得する
    timeD = static_cast<double>(GetNowHiPerformanceCount());
    gameTime = static_cast<double>(GetNowHiPerformanceCount()) / 1000000;
}

Clock::~Clock()
{
}

/// <summary>
/// タイマーを更新する
/// </summary>
void Clock::Update()
{
    // １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
    // 経過するまでここで待つ
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    while (temp < DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // 現在のカウントを取得する
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
    
    gameTime = timeD / 1000000;
}

double Clock::GetNowGameTime()
{
    return gameTime - Menu::GetOpenMenuTime();
}
