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
    /// 最終的なスコアの保存
    /// </summary>
    ResultScore(Timer* timer, std::shared_ptr<ObjectObserver> player);
    ~ResultScore() {};
    /// <summary>
    /// スコアの所得
    /// </summary>
    /// <returns></returns>
    int GetScore(ScoreKind scoreKind) const;
    
private:
    Timer* gameTimer;
    //ダメージ判定のあるオブジェクトに触れたらスコア減少
    static const int damageObjHitDec = 30;
    //残り時間のボーナス
    static const int timeBonus = 10;
    //一度も当たらなかった場合のスコア
    static const int noHitScore = 500;
    //コインはボーナス
    static const int coinBonus = 500;
    //プレイヤーの情報を渡してくれるやつ
    std::weak_ptr<ObjectObserver> playerObserver;
};

