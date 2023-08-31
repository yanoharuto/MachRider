#pragma once
#include "CountDown.h"
/// <summary>
/// ゲーム終了時のカウントダウン
/// </summary>
class EndCountDown :
    public CountDown
{
public:
    /// <summary>
    /// タイマーが切れそうになったらカウントダウンを表示する
    /// </summary>
    /// <param name="timer"></param>
    EndCountDown(Timer* timer);
    /// <summary>
    /// カウントダウンの数字と終わりを表示
    /// </summary>
    void DrawUI()const;
private:
    //カウントダウンの数字を薄く表示
    const int aValue = 130;
};

