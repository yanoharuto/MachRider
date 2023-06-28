#pragma once

/// <summary>
/// 決められた時間進んだりする
/// </summary>
class Timer
{
public:
    /// <summary>
    /// 制限時間とかを計測する
    /// </summary>
    /// <param name="setLimitTime"></param>
    Timer(double limitTime);
    ~Timer();
    ///<summary>
    ///時間をリセット
    ///</summary>
    void Init();
    /// <summary>
    /// 設定時間を過ぎたか
    /// </summary>
    /// <returns>過ぎたらTrue</returns>
    bool IsOverLimitTime()const;
    /// <summary>
    /// 計測時間
    /// </summary>
    /// <returns></returns>
    double GetElaspedTime()const;
    /// <summary>
    /// 最初に設定した制限時間を渡す
    /// </summary>
    /// <returns></returns>
    double GetLimitTime()const;
    /// <summary>
    /// 残り時間
    /// </summary>
    /// <returns></returns>
    double GetRemainingTime()const;
private:
    //制限時間
    double limitTime = 0;
    //計測開始時間
    double startTime = 0;
};

