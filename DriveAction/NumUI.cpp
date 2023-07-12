#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "UIDrawer.h"
/// <summary>
/// 数字を描画する
/// </summary>
NumUI::NumUI(UIKind kind)
{
    numData = UIManager::CreateUIData(kind);
    pointData = UIManager::CreateUIData(point);
    pointData.y = numData.y;
    pointData.size = numData.size;
}

NumUI::~NumUI()
{
}

void NumUI::Draw(int num) const
{
    Draw(numData.x, numData.y, num);
}

/// <summary>
/// 数字を描画したい時用
/// </summary>
/// <param name="x">一番右端</param>
/// <param name="y">Y座標</param>
/// <param name="num">数字</param>
/// <param name="scale">文字の大きさ</param>
/// <returns>左端の座標</returns>
int NumUI::Draw(int x, int y, int num) const
{
    //桁数
    int digits = static_cast<int>(OriginalMath::GetDigits(num));
    //表示位置を右端にいったん移動
    x -= static_cast<int> (numData.size * numData.width * digits);
    //桁数がゼロになるまで描画する　頭から描画する
    for (int i = digits; i > 0; i--)
    {
        //10のけたで割った時のあまり
        int drawNum = (static_cast<int>(num / pow(TIMER_FONT_NUM, i - 1))) % numData.dataHandle.size();
        //描画
        UIData data = numData;
        data.x = x;
        data.y = y;
        UIDrawer::DrawRotaUI(data,drawNum);
        //位置をずらす
        x += static_cast<int> (numData.size * numData.width);
        //次に描画したい数字の準備
        num -= static_cast<int>(drawNum * pow(TIMER_FONT_NUM, i - 1));
    }
    return x;
}
/// <summary>
/// 小数点も描画したい時用
/// </summary>
/// <param name="x">一番右端</param>
/// <param name="y">Y座標</param>
/// <param name="num">数字</param>
/// <param name="scale">文字の大きさ</param>
/// <returns>左端の座標</returns>
void NumUI::Draw(float num) const
{
    //整数部分
    int iNum = static_cast<int>(num);
    //小数第一位の部分
    int decimalNum1 = static_cast<int>((num - iNum) * 10);
    //小数部分第二位
    int decimalNum2 = static_cast<int>(((num - iNum) * 100 - decimalNum1 * 10));
    //描画終了した場所をedgeに渡す
    int edge = Draw(numData.x, numData.y, decimalNum2);
    edge -= static_cast<int> (numData.size * numData.width);
    edge = Draw(edge, numData.y, decimalNum1);
    edge -= static_cast<int> (numData.size * numData.width);
    //整数部分を描画
    Draw(edge, numData.y, iNum);
    edge -= static_cast<int> (numData.size * numData.width);
    //小数点
    UIData data = pointData;
    data.x = edge;
    UIDrawer::DrawRotaUI(data);
}
/// <summary>
/// 一文字の大きさ
/// </summary>
/// <returns></returns>
int NumUI::GetNumWidthSize()
{
    return numData.width;
}
