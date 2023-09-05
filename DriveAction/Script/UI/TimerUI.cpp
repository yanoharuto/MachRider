#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"

/// <summary>
/// 残り時間のセットと数字画像の読み込み
/// </summary>
/// <param name="setTimer">残り時間タイマー</param>
TimerUI::TimerUI(std::weak_ptr<Timer> setTimer)
{
    timer = setTimer;
    frameUI = UIManager::CreateUIData(timerFrame);
    pointUI = UIManager::CreateUIData(point);
    numUI = new NumUI(timeNum);
    //タイマーの枠の横位置
    frameX = frameUI.x + numUI->GetNumWidthSize() * 2;
}
/// <summary>
/// タイマーのロック解除
/// </summary>
TimerUI::~TimerUI()
{
    timer.reset();
}
/// <summary>
/// タイマーの残り時間を描画
/// </summary>
void TimerUI::Draw()
{
    //タイマーの枠を描画　中央にするために
    DrawRotaGraph( frameX , frameUI.y, frameUI.size, 0, frameUI.dataHandle[0], true);
    //残り時間の描画
    float limit = timer.lock()->GetRemainingTime();
    numUI->Draw(limit);
}