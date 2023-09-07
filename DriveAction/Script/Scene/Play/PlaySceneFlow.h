#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "SceneFlowBase.h"
#define PlaySceneProcesss 4
class PostGameEndStagingProcess;
class GamePrevProcess;
class PlayGameProcess;
class ActorControllerManager;
class GameCamera;
class ShadowMap;
class ConflictManager;
class GameScreen;
class PlayerObserver;
class CollectItemObserver;
/// <summary>
/// どういう順番で処理を行うか決める
/// </summary>
class PlaySceneFlow final : public SceneFlowBase
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    PlaySceneFlow();
    /// <summary>
    /// オブジェクトやカメラ、UIタイマーなどを削除
    /// </summary>
    ~PlaySceneFlow()override;
    /// <summary>
    /// プレイシーンの更新
    /// </summary>
    /// <returns></returns>
    void Update() override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// プレイシーンの段階
    /// </summary>
    enum PlaySceneProgress
    {
        start,
        game,
        playerGoal,
        end
    };
    /// <summary>
    /// 遊んでいるときの処理
    /// </summary>
    void GameUpdate();
    /// <summary>
    /// ゴール後の処理
    /// </summary>
    void PlayerGoalUpdate();
    /// <summary>
    /// 最後の処理
    /// </summary>
    void EndUpdate();
    /// <summary>
    /// 初めにする処理
    /// </summary>
    void StartUpdate();
    //各シーンの処理の関数ポインタ
    void (PlaySceneFlow::*UpdateFunc[PlaySceneProcesss])();
    //ゴール後の処理
    PostGameEndStagingProcess* postGoalStaging;
    //遊んでいるときの処理
    PlayGameProcess* playGameProcess;
    //レース前の処理
    GamePrevProcess* gamePrevProcess;
    //カメラ
    GameCamera* camera;
    //シャドウマップ
    ShadowMap* shadowMap;
    //衝突判判定クラス
    ConflictManager* conflictManager;
    //各オブジェクトの管理役
    std::shared_ptr<ActorControllerManager> controllerManager;
    //プレイヤーの情報通達クラス
    std::shared_ptr<PlayerObserver> playerObserver;
    //収集アイテムの管理クラス
    std::shared_ptr<CollectItemObserver>  collectItemObserver;
    //描画状況を保存する
    GameScreen* screen;
    //今何の処理を行うか決める変数
    PlaySceneProgress nowProgress;
};