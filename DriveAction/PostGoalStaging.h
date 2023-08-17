#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"

class PlayerObserver;
class NumUI;
class FlashUI;
class Timer;
class TimerUI;
class ScoreNum;
/// <summary>
/// スコアの表示
/// </summary>
struct ScoreUI
{
    UIData scoreKindData = {};//スコアの種類を描画する
    int score = 0;//スコア量
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
    PostGoalStaging(Timer* timer, std::weak_ptr<PlayerObserver> player);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// スコアの数字を徐々に出していく処理
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
    /// クリアタイムのスコア変換
    /// </summary>
    void ConvertTimeScotre();
    /// <summary>
    /// 収集アイテムのスコア変換
    /// </summary>
    void ConvertCollectScotre();
    /// <summary>
    /// ゲーム終了のアナウンスを流すプロセス
    /// </summary>
    void EndAnnounceProcess();
    /// <summary>
    /// スコアに関するUIを所得
    /// </summary>
    /// <param name="kind"></param>
    /// <returns></returns>
    ScoreUI GetScoreUI(UIKind kind);
    /// <summary>
    /// 残り時間スコアの描画
    /// </summary>
    void TimeScoreDraw() const;
    /// <summary>
    /// 収集アイテムスコアの描画
    /// </summary>
    void CollectScoreDraw() const;
    //終了アナウンス
    bool isEndFinishAnnounce = false;
    //処理をすべて行えたら
    bool isEndProcess = false;
    //合計スコアを描画したか
    bool isEndConvertScore = false;
    //クリアタイム
    float clearTime = 0;
    //後ろの画面の明るさを低くする
    const int backScreenBright = 60;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //表示するスコアが変動していく時間
    const float scoreLarpTime = 3.0f;
    //終了アナウンスに掛かる時間
    const float finishAnounceTime = 3.0f;
    //描画するクリアタイム　スコアに換算していく
    float drawClearTime = 0;
    //描画する収集アイテムの数
    int drawCollectIconNum = 0;
    //舞い散る花びら
    int confettiEffect = -1;
    //ゲットしたアイテムの数
    int getCollectNum = 0;
    //ゲーム終了時の画面
    int gameEndScreen = -1;
    //スペースキー催促
    FlashUI* switchUI;
    //合計スコア
    ScoreUI totalScoreUI;
    //収集アイテムを集めて得るスコア
    ScoreUI collectScoreUI;
    //残り時間ボーナススコア
    ScoreUI timeScoreUI;
    //ハイスコアの更新
    UIData hiScoreUI;
    //終わりのアナウンス
    UIData finishAnnounceData;
    //収集アイテムのデータ
    UIData collectData;
    //クリアタイムを表示する用
    NumUI* clearTimeUI;
    //合計スコア表示
    ScoreNum* totalScoreNumUI;
    //今何の処理を行っているか
    ResultScore::ScoreKind nowConvertScore;
    //スコアを徐々に変換するためのタイマー
    Timer* larpConvertScoreTimer;
    //ゴールアナウンスが表示されきるまでの時間を計測する
    Timer* larpMoveAnnounceTimer;
    //スコアの保存
    ResultScore* resultScore;
    //スペースキー催促UI
    FlashUI* pressSpaceKeyUI;
    //拍手効果音
    bool isSoundClapSE = false;
};
