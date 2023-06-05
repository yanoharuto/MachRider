#pragma once
#include <string>
#include "Utility.h"
#include "DxLib.h"
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SwitchUI;
class Timer;

/// <summary>
/// スコアの表示
/// </summary>
struct ScoreUI
{
    UIData data;
    int score;
    NumUI* ui;
};
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
    bool Update();
    /// <summary>
    /// スコアの描画
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// スコアに関するUIの初期化
    /// </summary>
    /// <param name="kind"></param>
    /// <param name="index"></param>
    void InitScoreUI(UIKind kind,int index);
    //終了アナウンス
    int spaceClickCount = 0;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //スペースキーを押す合間
    const float spaceKeyCoolTime = 1.5f;
    //終了のアナウンスの色
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //スペースキー催促
    SwitchUI* switchUI;
    //各スコアを表示するための配列
    ScoreUI scoreUI[SCORE_KIND_NUM] = { {},{},{},{} };
    //ゴールしたときの終了アナウンス
    //タイマー
    Timer* timer;
};
