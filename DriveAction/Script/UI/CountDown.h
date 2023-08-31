#pragma once
#include <string>
#include "DxLib.h"
#include "Timer.h"
#include "UIManager.h"
/// <summary>
/// カウントダウンのUI
/// </summary>
class CountDown
{
public:
    /// <summary>
    /// カウントダウンのUI
    /// </summary>
    /// <param name="setTimer">何秒計るか</param>
    CountDown(Timer* timer);
    /// <summary>
    /// 特になし
    /// </summary>
    ~CountDown() {};
    /// <summary>
    /// タイマーを進ませてUIの数字を変更する
    /// </summary>
    void Update();
    /// <summary>
    /// カウントダウンが終わったか
    /// </summary>
    /// <returns></returns>
    bool IsCountDownEnd()const;
    /// <summary>
    /// カウントダウンの音が鳴り終わったか
    /// </summary>
    /// <returns></returns>
    bool IsPlayCountDownSound()const;
    /// <summary>
    /// カウントダウンの数字の描画
    /// </summary>
    virtual void DrawUI()const;
protected:
    //カウントダウンが終わったか
    bool isCountDownEnd = false;
    //カウントダウン効果音を鳴らしたか
    bool isPlayedCountSE = false;
    //カウントダウンのUI
    UIData countDownUIData;
    //終わり時のUI
    UIData endUI;
    //カウントダウンUIの画像を変更するための添え字
    int uiHIndex = -1;
    //カウントダウンを数えるタイマー
    Timer* timer;
};