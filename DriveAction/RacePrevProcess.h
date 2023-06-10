#pragma once

#include <string>

#include "UIManager.h"
class Timer;
class CountDown;
/// <summary>
/// レース前の処理やってくれる
/// </summary>
class RacePrevProcess
{
public:
    RacePrevProcess();
    ~RacePrevProcess();
    //更新
    void Update();
    //描画
    void Draw();
    //終了したら
    bool IsProccesEnd();
private:
    //収集物のアイコン
    UIData collectIconData;
    //操作説明のUI
    UIData manualData;
    //ゲームの目標
    UIData gamePuroseData;
    //コマ送り用タイマー
    Timer* frameByFrameTimer;
    //カウントダウン用のタイマー
    Timer* countDownTimer;
    //ゲームを始める前のカウントダウン
    CountDown* countDown;
    //処理終了したか
    bool proccesEnd = false;
    //現在のコマ
    int iconIncrement = 0;
};