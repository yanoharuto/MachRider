#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "SceneFlowBase.h"

#define PlaySceneProccess 4
class ObjectObserver;
class AssetManager;
class ConflictManager;
class EffectManager;
class PostGoalStaging;
class GamePlayUI;
class RaceCamera;
class ResultScore;
class RaceScreen;
class RacePrevProcess;
class ShadowMap;
class ReusableTimer;
class UIManager;
class ActorControllerManager;
class EnemyGenerator;
/// <summary>
/// どういう順番で処理を行うか決める
/// </summary>
class PlaySceneFlow final:public SceneFlowBase
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    PlaySceneFlow();
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
    enum PlaySceeneProgress
    {
        start,
        game,
        playerGoal,
        end
    };
    /// <summary>
    /// マネージャーの描画関数を呼び出す
    /// </summary>
    void DrawManagers()const;
    /// <summary>
    /// シャドウマップを使った描画
    /// </summary>
    void UseShadowMapDraw()const;
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
    void (PlaySceneFlow::*UpdateFunc[PlaySceneProccess])();
    //カメラ
    RaceCamera* camera;
    //ゴール後の処理
    PostGoalStaging* postGoalStaging;
    //プレイヤー関係のUI
    GamePlayUI* playerUI;
    //当たり判定処理
    ConflictManager* conflictManager;
    //今何の処理を行うか決める変数
    PlaySceeneProgress nowProgress;
    //レース前の処理
    RacePrevProcess* racePrevProccess;
    //ゲーム終了タイマー
    ReusableTimer* gameLimitTimer;
    //こいつを回してプレイヤーとか敵を動かす
    ActorControllerManager* controllerManager;
    //シャドウマップ
    ShadowMap* shadowMap;
    //レース中の描画した物を保存する
    RaceScreen* screen;
    //プレイヤーの位置や向いている方向を教えてくれる
    std::weak_ptr<ObjectObserver> player;
};