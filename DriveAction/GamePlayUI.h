#pragma once
#include <iostream>
#include <memory>
#include <list>
#include "Utility.h"
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class ObjectObserver;
class CountDown;
class Player;
class ChallengeFlow;
class CollectSign;
/// <summary>
/// プレイヤーに関係のあるUI
/// </summary>
class GamePlayUI final
{
public:
    GamePlayUI(Timer* setTimer,ChallengeFlow* challengeFlow, std::shared_ptr<ObjectObserver> player);
    ~GamePlayUI();
    /// <summary>
    /// ミニマップの更新　やコインの枚数を更新
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(ChallengeFlow* challengeFlow);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const;
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
    UIData slashData;  
    //収集アイテムのマーカー
    UIData collectSignData;
    //カウントダウン
    CountDown* countDown;
    //プレイヤーの位置とかコインの所得数などを教えてくれる奴
    std::weak_ptr<ObjectObserver> playerObserver;
    CollectSign* cSign;
};