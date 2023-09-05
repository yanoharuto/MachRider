#pragma once
#include <iostream>
#include <memory>
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class PlayerObserver;
class EndCountDown;
class PlayerCarController;
class EnemyGenerator;
class CollectCompass;
class PlayManual;
class GameManager;
class ReusableTimer;
/// <summary>
/// 遊んでいるときのUI
/// </summary>
class GamePlayUI final
{
public:
    GamePlayUI(std::weak_ptr<GameManager> manager, std::weak_ptr<Timer> timer);
    /// <summary>
    /// 各UIを解放
    /// </summary>
    ~GamePlayUI();
    /// <summary>
    /// ミニマップの更新や収集アイテムの枚数を更新
    /// </summary>
    void Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const;
private:
    //最初の収集アイテムの枚数
    int firstCoinNum = 0;
    // プレイヤーが所得した枚数
    int nowGetCoinNum = 0;
    //残りの収集アイテム数を表示するか
    bool isDrawGetNum = false;
    //残りの収集アイテム数を表示する時間
    float remainingNumDrawTime = 2.0f;
    //残った収集アイテムの数を表示する時間を計る
    ReusableTimer* remainingNumDrawTimer = nullptr;
    //ゲーム残り時間タイマー
    TimerUI* gameTimerUI;
    //ミニマップ
    MiniMap* minimapUI;
    //最初の収集アイテムの枚数を描画するクラス
    NumUI* firstCollectNumUI;
    //ゲットした収集アイテムの枚数を描画
    NumUI* getNumUI;
    //残った収集アイテムの数
    NumUI* remainingNumUI;
    //残り収集アイテムについてのフレーズ
    UIData remainingFrazeUI;
    //数字の間に置くスラッシュ
    UIData frameUI;  
    //収集アイテムのマーカー
    UIData collectSignData;
    //カウントダウン
    EndCountDown* countDown;
    //プレイヤーの位置とか収集アイテムの所得数などを教えてくれる奴
    std::weak_ptr<PlayerObserver> playerObserver;
    //収集アイテムの方向とかを教えてくれる
    CollectCompass* cSign;
    //プレイヤーの操作方法
    PlayManual* playManual;
};