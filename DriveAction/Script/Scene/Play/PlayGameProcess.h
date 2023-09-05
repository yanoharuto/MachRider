#pragma once
#include <iostream>
#include <memory>
class PlayerObserver;
class GamePlayUI;
class GameManager;
class StopTimer;
class Timer;
/// <summary>
/// ゲーム中の処理役
/// </summary>
class PlayGameProcess
{
public:
    /// <summary>
    /// プレイヤーの位置をUIに渡す
    /// </summary>
    /// <param name="manager">UIにプレイヤーの位置を渡す</param>
    PlayGameProcess(std::weak_ptr<GameManager> const manager);
    /// <summary>
    /// UIとタイマーの解放
    /// </summary>
    ~PlayGameProcess();
    /// <summary>
    /// 遊んでいるときの更新
    /// </summary>
    /// <param name="manager">ゲームをするときに必要なオブジェクト</param>
    void Update(std::weak_ptr<GameManager> const manager);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const;
    /// <summary>
    /// ゲーム部分の処理の終了
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess()const
    {
        return isEndProcess;
    };
    /// <summary>
    /// ゲームの残り時間タイマーを渡す
    /// </summary>
    /// <returns> ゲームの残り時間タイマーを渡す</returns>
    std::shared_ptr<Timer> GetGameTimer();
    
private:
    //制限時間のタイマー
    std::shared_ptr<StopTimer> timer;
    //遊んでいるときのUI
    GamePlayUI* playUI;
    //処理終了フラグ
    bool isEndProcess;
};