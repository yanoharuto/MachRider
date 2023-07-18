#pragma once

//fps
#define FLAME 60
/// <summary>
/// ゲーム内の時間を更新
/// </summary>
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// タイマーを更新する
    /// </summary>
    void Update();
    /// <summary>
    /// 1000m秒を普通の秒数にして渡す
    /// </summary>
    /// <returns></returns>
    static double GetNowGameTime();
private:
    //1000m秒
    double timeD;
    //普通の経過秒数
    static double gameTime;
};