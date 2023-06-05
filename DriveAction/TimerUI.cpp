#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"


TimerUI::TimerUI(Timer* setTimer)
{
    timer = setTimer;
    frameData = UIManager::CreateUIData(timerFrame);
    pointData = UIManager::CreateUIData(point);
    numUI = new NumUI(timeNum);
    timerFontLoadSize = numUI->GetNumWidthSize();
}

TimerUI::~TimerUI()
{
    DeleteGraph(pointGraphHandle);
}

void TimerUI::Draw()
{
    //ŠÔ
    DrawRotaGraph(frameData.x + timerFontLoadSize * 2, frameData.y, frameData.size, 0, frameData.dataHandle[0], true);
    float limit = timer->GetLimitTime();
    numUI->Draw(limit);
}