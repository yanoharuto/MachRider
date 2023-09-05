#pragma once
#include <iostream>
#include <memory>
class GameCamera;
class ShadowMap;
class ConflictManager;
class ActorControllerManager;
class PlayerObserver;
class GameScreen;
class ReusableTimer;
class Timer;
/// <summary>
/// ゲームで動かすために必要な物をまとめたもの
/// </summary>
class GameManager final
{
public:
    /// <summary>
    /// カメラや当たり判定やゲームオブジェクトなどを確保
    /// </summary>
    GameManager();
    /// <summary>
    /// 各クラスを開放
    /// </summary>
    ~GameManager();
    /// <summary>
    /// 各クラスの更新
    /// </summary>
    void Update();
    /// <summary>
    /// ゲーム始める前の更新
    /// </summary>
    void PrepareGame();
    /// <summary>
    /// 描画画面を保存
    /// </summary>
    void SaveDrawScreen();
    /// <summary>
    /// 各オブジェクトの描画と影を描画
    /// </summary>
    void DrawActor()const;
    /// <summary>
    /// プレイヤーの情報通達クラスを渡す
    /// </summary>
    /// <returns>プレイヤーの情報通達クラス</returns>
    std::weak_ptr<PlayerObserver> GetPlayerObserver();
private:
    //プレイヤーの情報通達クラス
    std::weak_ptr<PlayerObserver> playerObserver;
    //カメラ
    GameCamera* camera;
    //シャドウマップ
    ShadowMap* shadowMap;
    //衝突判判定クラス
    ConflictManager* conflictManager;
    //各オブジェクトの管理役
    ActorControllerManager* controllerManager;
    //描画状況を保存する
    GameScreen* screen;
};