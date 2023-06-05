#pragma once
#include <list>
#include "Utility.h"
#include "UIManager.h"
class CoinManager;
//収集アイテムのマップ
class MiniMap;
//残り時間を表示してくれる
class TimerUI;
//ゲームの残り時間とかのタイマー
class Timer;
//数字に関するUI
class NumUI;
//情報を更新してくれる
class ObjectSubject;
//Subjectを見ている
class ObjectObserver;
//走ってるやつのマネージャー
class RacerManager;
//カウントダウン
class CountDown;
/// <summary>
/// プレイヤーに関係のあるUI
/// </summary>
class PlayerRelatedUI final
{
public:
    PlayerRelatedUI(Timer* setTimer,int setFirstCoinNum,RacerManager* manager);
    ~PlayerRelatedUI();
    /// <summary>
    /// ミニマップの更新　やコインの枚数を更新
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(CoinManager* coinManager);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //最初のコインの枚数
    int firstCoinNum = 0;
    // プレイヤーが所得した枚数
    int nowGetCoinNum = 0;
    //タイマー
    TimerUI* timerUI;
    //ミニマップ
    MiniMap* minimapUI;
    //最初のコインの枚数を描画するクラス
    NumUI* firstNumUI;
    //ゲットしたコインの枚数を描画
    NumUI* getNumUI;
    //操作説明のUI情報
    UIData manualData;
    //スラッシュ
    UIData slashHandle;  
  
    //フォントのサイズ
    const int fontSize = 1;
    //プレイヤーの位置とかコインの所得数などを教えてくれる奴
    ObjectObserver* playerObserver;
};