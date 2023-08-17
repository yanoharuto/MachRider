#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "UIDrawer.h"
#include <fstream>
#include <string>
/// <summary>
/// 合計スコアを表示する
/// </summary>
ScoreNum::ScoreNum()
    :NumUI(totalScoreNum)
{
    ScoreBorder info = StageDataManager::GetScoreBorder();
    first = info.gold;
    second = info.silver;
    third = info.bronze;
}

ScoreNum::~ScoreNum()
{
}
/// <summary>
/// スコアによって大きさ変更
/// </summary>
/// <param name="num"></param>
void ScoreNum::Draw(int num)const
{
    VECTOR numColor = firstColor;
    UIData data = numData;
    //スコアの段階によって色と大きさを変更する
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

    //スコアの描画
    SetDrawBright(numColor.x,numColor.y,numColor.z);
    NumUI::Draw(data, num);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}