#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class Timer;
class ObjectObserver;

/// <summary>
/// 最終的なスコアの保存役
/// </summary>
class ResultScore
{
public:
    enum ScoreKind
    {
        time = 0,
        collect = 1,
        hit = 2,
        total = 3
    };
    /// <summary>
    /// スコア所得
    /// </summary>
    /// <param name="scoreKind">どのスコアが欲しいか</param>
    /// <returns></returns>
    static int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// スコアを確定させる
    /// </summary>
    /// <param name="timer"></param>
    /// <param name="player"></param>
    static void FixScore(Timer* timer, std::weak_ptr<ObjectObserver> player);
private:

    /// <summary>
    /// 最終的なスコアの保存
    /// </summary>
    ResultScore() {};
    ~ResultScore() {};
    static int timeScore;
    static int collectScore;
    static bool noHit;
    //ダメージ判定のあるオブジェクトに触れたらスコア減少
    static const int damageObjHitDec = 30;
    //残り時間のボーナス
    static const int timeBonus = 10;
    //一度も当たらなかった場合のスコア
    static const int noHitScore = 500;
    //コインはボーナス
    static const int coinBonus = 500;
    
};

