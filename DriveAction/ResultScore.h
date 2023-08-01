#pragma once
#include <iostream>
#include <memory>
#define SCORE_KIND_NUM 4
class Timer;
class PlayerObserver;

/// <summary>
/// 最終的なスコアの保存役
/// </summary>
class ResultScore
{
public:
    /// <summary>
/// 最終的なスコアの保存
/// </summary>
    ResultScore() {};
    ~ResultScore() {};
    enum ScoreKind
    {
        timeBonus = 0,
        collectBonus = 1,
        total = 2
    };
    /// <summary>
    /// スコア所得
    /// </summary>
    /// <param name="scoreKind">どのスコアが欲しいか</param>
    /// <returns></returns>
    int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// スコアの倍率を所得
    /// </summary>
    /// <param name="scoreKind"></param>
    /// <returns></returns>
    int GetScoreBonus(ScoreKind scoreKind);
    /// <summary>
    /// スコアを確定させる
    /// </summary>
    /// <param name="timer"></param>
    /// <param name="player"></param>
    void FixScore(Timer* timer, std::weak_ptr<PlayerObserver> player);
private:
    //残り時間のスコア
    int timeScore = 0;
    //収集アイテムを集めたスコア
    int collectScore = 0;
    //残り時間のボーナス
    static const int clearTimeBonus;
    //コインはボーナス
    static const int getCollectBonus;
};

