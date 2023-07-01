#pragma once
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SpaceKeyUI;
class Timer;

/// <summary>
/// スコアの表示
/// </summary>
struct ScoreUI
{
    UIData scoreKindData;//スコアの種類を描画する
    int score;//スコア量
    bool draw;//描画するかどうか
    NumUI* numUI;//スコア量を描画する
};
using enum ResultScore::ScoreKind;
/// <summary>
/// ゴール後の演出をする
/// </summary>
class PostGoalStaging final
{
public:
    /// <summary>
    /// ゴール後の演出をする
    /// </summary>
    PostGoalStaging();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// スコアを徐々に渡す
    /// </summary>
    /// <returns></returns>
    void Update();
    /// <summary>
    /// スコアの描画
    /// </summary>
    void Draw()const;
    /// <summary>
    /// 処理を終了したか
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const;
private:
    /// <summary>
    /// 今やるべき処理を所得
    /// </summary>
    /// <returns></returns>
    void GetNextProcess();
    /// <summary>
    /// スコアに関するUIの追加
    /// </summary>
    /// <param name="scoreKind">追加するUI</param>
    void AddScoreUI(ResultScore::ScoreKind scoreKind);
    //処理をすべて行えたら
    bool isEndProcess = false;
    //合計スコアを描画したか
    bool isDrawTotalScore = false;
    //後ろの画面の明るさを低くする
    const int backScreenBright = 60;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //表示するスコアが変動していく時間
    const float scoreChangeTime = 0.2f;
    //ゲーム終了時の画面
    int gameEndScreen = -1;
    //スペースキー催促
    SpaceKeyUI* switchUI;
    //各スコアを表示するための配列
    std::unordered_map<ResultScore::ScoreKind,ScoreUI> scoreUI;
    //今何の処理を行っているか
    ResultScore::ScoreKind nowProcess;
    //タイマー
    Timer* timer;
};
