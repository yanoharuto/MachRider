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
    /// ゲームクリアしたときのスコアを計算する
    /// </summary>
    /// <param name="timer">クリアタイム</param>
    /// <param name="player">クリアしたプレイヤーの情報通達役</param>
    ResultScore(Timer* timer, std::weak_ptr<PlayerObserver> player);
    /// <summary>
    /// 特になし
    /// </summary>
    ~ResultScore(){};
    //スコアの種類
    enum ScoreKind
    {
        //残り時間ボーナス
        timeBonus = 0,
        //収集アイテムボーナス
        collectBonus = 1,
        //合計
        total = 2
    };
    /// <summary>
    /// スコア所得
    /// </summary>
    /// <param name="scoreKind">欲しいスコアの種類</param>
    /// <returns>引数のスコア量</returns>
    int GetScore(ScoreKind scoreKind);
    /// <summary>
    /// スコアの倍率を所得
    /// </summary>
    /// <param name="scoreKind">欲しいスコアの種類</param>
    /// <returns>引数のスコアの倍率</returns>
    int GetScoreBonus(ScoreKind scoreKind);

    /// <summary>
    /// ハイスコアが更新されたか
    /// </summary>
    /// <returns>ハイスコアが更新されていたらTrue</returns>
    bool IsUpdateHiScore();
private:
    /// <summary>
    /// スコアを確定させる
    /// </summary>
    /// <param name="timer">クリアタイム所得</param>
    /// <param name="player">プレイヤーの所得した収集アイテムを調べる</param>
    void FixScore(Timer* const timer, std::weak_ptr<PlayerObserver> player);
    //残り時間のスコア
    int timeScore = 0;
    //収集アイテムを集めたスコア
    int collectScore = 0;
    //ハイスコア更新フラグ
    bool isUpdateHiScore = false;
    //残り時間のボーナス
    static const int clearTimeBonus;
    //コインはボーナス
    static const int getCollectBonus;
};

