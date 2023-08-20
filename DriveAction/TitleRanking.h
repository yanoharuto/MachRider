#pragma once
#include "UIManager.h"
#include "DxLib.h"
class NumUI;
/// <summary>
/// タイトルで各ステージのスコアランキング上位三名を描画
/// </summary>
class TitleRanking
{
public:
    /// <summary>
    /// タイトルで各ステージのスコアランキング上位三名を描画
    /// </summary>
    TitleRanking();
    /// <summary>
    /// ランキングを構成する数字UIを消去
    /// </summary>
    ~TitleRanking();
    /// <summary>
    /// ランキングの上位三名を描画
    /// </summary>
    void Draw()const;
private:
    /// <summary>
    /// 引数の要素を描画
    /// </summary>
    /// <param name="ui">使いたい数字描画UI</param>
    /// <param name="num">描画したい数字</param>
    /// <param name="color">数字の色</param>
    void Draw(NumUI* ui,int num,VECTOR color)const;
    //そのステージの中で一番いいスコア
    NumUI* highUI;
    //2番目に良いスコア
    NumUI* secondUI;
    //3番目にいいスコア
    NumUI* thirdUI;
    //１の順位UI
    NumUI* highRankUI;
    //２の順位UI
    NumUI* secondRankUI;
    //3の順位UI
    NumUI* thirdRankUI;
    //ランキング
    UIData rankUI;

    //一番いいスコアの色
    const VECTOR firstColor = VGet(255, 215, 0);
    //ちょっといいときの色
    const VECTOR thirdColor = VGet(196, 112, 34);
    //二番目にいい時の色
    const VECTOR secondColor = VGet(192, 192, 192);

};