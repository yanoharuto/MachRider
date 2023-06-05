#pragma once

//fps
#define FLAME 60
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// タイマーを更新する
    /// </summary>
    void Update();

    static double GetNowGameTime();
private:

    double timeD;
    double openMenuTime;
    static double gameTime;
    static double totalOpenMenuTime;
    //メニューを開いた時間
    static double openStartMenuTime;
};