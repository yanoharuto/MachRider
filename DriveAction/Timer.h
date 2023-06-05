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
    Timer(float limitTime);
    ~Timer();
    ///<summary>
    ///時間をリセット
    ///</summary>
    void Init();
    /// <summary>
    /// 設定時間を過ぎたか
    /// </summary>
    /// <returns>過ぎたらTrue</returns>
    bool IsOverLimitTime();
    /// <summary>
    /// 計測時間
    /// </summary>
    /// <returns></returns>
    float GetLimitTime();
private:
    //制限時間
    float limitTime = 0;
    //計測開始時間
    double startTime = 0;
};

