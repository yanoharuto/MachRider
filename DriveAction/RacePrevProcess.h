#pragma once

#include <string>
#include "UIManager.h"
class NumUI;
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
    /// <summary>
    /// カウントダウンの更新
    /// </summary>
    void Update();
    /// <summary>
    /// 遊び方とカウントダウンの描画
    /// </summary>
    void Draw() const;
    /// <summary>
    /// 処理が終了したか
    /// </summary>
    /// <returns></returns>
    bool IsProccesEnd();
private:
    //収集物のアイコン
    UIData collectIconData;
    //操作説明のUI
    UIData manualData;
    //ゲームの目標
    UIData gamePuroseData;
    //収集アイテムの集める数
    NumUI* collectItemNum;
    //コマ送り用タイマー
    Timer* frameByFrameTimer;
    //カウントダウン用のタイマー
    Timer* countDownTimer;
    //ゲームを始める前のカウントダウン
    CountDown* countDown;
    //処理終了したか
    bool proccesEnd = false;
    //収集アイテムアイコンのコマ割り番号
    int iconGHIndex = 0;
    //ゲームの目標説明をしている間は周りを白くする
    int fadeValue = 0;
    //スタートのカウントダウンは5秒
    const float startTimerLimit = 5;
};