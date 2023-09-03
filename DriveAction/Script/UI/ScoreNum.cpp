#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "UIDrawer.h"
#include <fstream>
#include <string>
/// <summary>
/// スコアの評価の線引きを所得
/// </summary>
ScoreNum::ScoreNum()
    :NumUI(totalScoreNum)
{
    ScoreBorder info = StageDataManager::GetScoreBorder();
    first = info.gold;
    second = info.silver;
    third = info.bronze;
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