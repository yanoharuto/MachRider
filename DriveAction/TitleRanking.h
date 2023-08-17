#pragma once
#include "UIManager.h"
#include "DxLib.h"
class NumUI;
class TitleRanking
{
public:
    TitleRanking();
    ~TitleRanking();
    
    void Draw()const;
private:
    void Draw(NumUI* ui,int score,VECTOR color)const;
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