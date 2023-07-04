#pragma once
#include <iostream>
#include <memory>
#include <list>

class MiniMap;
class TimerUI;
class Timer;
class NumUI;
class HitCountObserver;
class EndCountDown;
class Player;
class EnemyGenerator;
class CollectSign;
/// <summary>
/// 遊んでいるときのUI
/// </summary>
class GamePlayUI final
{
public:
    GamePlayUI(Timer* setTimer,std::weak_ptr<HitCountObserver> player);

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
    Timer* remainingNumDrawTimer = nullptr;
    //ゲーム残り時間タイマー
    TimerUI* gameTimerUI;
    //ミニマップ
    MiniMap* minimapUI;
    //最初の収集アイテムの枚数を描画するクラス
    NumUI* firstNumUI;
    //ゲットした収集アイテムの枚数を描画
    NumUI* getNumUI;
    //残った収集アイテムの数
    NumUI* remainingNumUI;
    //残り収集アイテムについてのフレーズ
    UIData remainingFraze;
    //数字の間に置くスラッシュ
    UIData slashData;  
    //収集アイテムのマーカー
    UIData collectSignData;
    //カウントダウン
    EndCountDown* countDown;
    //プレイヤーの位置とか収集アイテムの所得数などを教えてくれる奴
    std::weak_ptr<HitCountObserver> playerObserver;
    //収集アイテムの方向とかを教えてくれる
    CollectSign* cSign;
};