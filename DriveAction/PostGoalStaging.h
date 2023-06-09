#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "UIManager.h"
#include "ResultScore.h"

class ObjectObserver;
class NumUI;
class FlashUI;
class Timer;
class TimerUI;
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
    PostGoalStaging(Timer* timer, std::weak_ptr<ObjectObserver> player);
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
    /// 今やるべき処理
    /// </summary>
    /// <returns></returns>
    void UpdateNowProcess();
    /// <summary>
    /// スコアに関するUIを所得
    /// </summary>
    /// <param name="kind"></param>
    /// <returns></returns>
    ScoreUI GetScoreUI(UIKind kind);
    //終了アナウンス
    bool isEndFinishAnnounce = false;
    //処理をすべて行えたら
    bool isEndProcess = false;
    //合計スコアを描画したか
    bool isEndUpdateScore = false;
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
    //終わりのアナウンス
    UIData finishAnnounceData;
    //収集アイテムのデータ
    UIData collectData;
    //クリアタイムを表示する用
    NumUI* clearTimeUI;
    //合計スコア表示
    NumUI* totalScoreNumUI;
    //今何の処理を行っているか
    ResultScore::ScoreKind nowProcess;
    //タイマー
    Timer* larpTimer;
    //スコア換算処理が始まるまでの時間
    Timer* startScoreExchangeTimer;
    //スコアの保存
    ResultScore* resultScore;
    //スペースキー催促UI
    FlashUI* pressSpaceKeyUI;
    struct ScoreColor
    {
        int r, g, b;
    };
    //総合スコアの色
    ScoreColor totalScoreColor;
    //総合スコアデフォルトカラー
    const ScoreColor bronze = { 123,40,0 };
    //ちょっと良くなった時の色
    const ScoreColor silver = { 192,192,192 };
    //総合スコアがかなり良いときの色
    const ScoreColor gold = {255, 215, 0};
};
