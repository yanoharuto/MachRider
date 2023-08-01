#pragma once
#include "NumUI.h"
#include "DxLib.h"
/// <summary>
/// 合計スコアの表示
/// </summary>
class ScoreNum :
    public NumUI
{
public:
    ScoreNum();
    ~ScoreNum();
    /// <summary>
    /// スコアによって大きさ変更
    /// </summary>
    /// <param name="num"></param>
    void Draw(int num)const override;
private:
    //上手にクリアしたときのスコアのライン
    int first = 0;
    //普通にクリアしたときのスコアのライン
    int second = 0;
    //なんとかクリアしたときのスコアのライン
    int third = 0;
    //secondより上のスコアになった時の文字のフォント
    float secondBorderFontSize = 0.9f;
    //thirdより上のスコアになった時の文字のフォント
    float thirdBorderFontSize = 0.85f;
    //thirdより下のスコアになった時の文字のフォント
    float thirdUnderFontSize = 0.8f;

    VECTOR firstColor = VGet(255,215,0);
    VECTOR secondColor = VGet(192,192,192);
    VECTOR thirdColor = VGet(196,112,34);
    VECTOR thirdUnderColor = VGet(176,92,14);
};

