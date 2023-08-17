#include "ScoreNum.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "UIDrawer.h"
#include <fstream>
#include <string>
/// <summary>
/// ���v�X�R�A��\������
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
/// �X�R�A�ɂ���đ傫���ύX
/// </summary>
/// <param name="num"></param>
void ScoreNum::Draw(int num)const
{
    VECTOR numColor = firstColor;
    UIData data = numData;
    //�X�R�A�̒i�K�ɂ���ĐF�Ƒ傫����ύX����
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

    //�X�R�A�̕`��
    SetDrawBright(numColor.x,numColor.y,numColor.z);
    NumUI::Draw(data, num);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
}