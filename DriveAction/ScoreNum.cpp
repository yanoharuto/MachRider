#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
ScoreNum::ScoreNum()
    :NumUI(totalScoreNum)
{
    ScoreBorder info = StageDataManager::GetScoreBorder();
    first = info.first;
    second = info.second;
    third = info.third;
}

ScoreNum::~ScoreNum()
{
}

void ScoreNum::Draw(int num)const
{
    VECTOR numColor = firstColor;
    UIData data = numData;
    if (num < third)
    {
        numColor = thirdUnderColor;
        data.size = numData.size * thirdUnderFontSize;
    }
    else if (num < second)
    {
        numColor = thirdColor;
        data.size = numData.size * thirdBorderFontSize;
    }
    else if (num < first)
    {
        numColor = secondColor;
        data.size = numData.size * secondBorderFontSize;
    }
    SetDrawBright(numColor.x,numColor.y,numColor.z);
    NumUI::Draw(data, num);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}
