#pragma once
#include "SceneBase.h"
#include <string>
#include <iostream>
#include <memory>
//四つに分けて処理を行う

#define PlaySceneProcess 3
class Menu;
class PostGameEndStagingProcess;
class PrePlayGameProcess;
class PlayGameProcess;
class ActorControllerManager;
class GameCamera;
class ShadowMap;
class ConflictManager;
class GameScreen;
class PlayerObserver;
class CollectItemObserver;
/// <summary>
/// ゲームを遊ぶシーン
/// </summary>
class PlayScene final: public SceneBase
{
public:
    /// <summary>
    /// メニュー画面とゲームの流れの確保と音をロード
    /// </summary>
    PlayScene();
    /// <summary>
    /// メニューとゲームの開放
    /// </summary>
    ~PlayScene() override;
    /// <summary>
    /// ゲームを遊ぶ
    /// </summary>
    /// <returns></returns>
    SceneType Update() override;
    /// <summary>
    /// メニューを開いている時と遊んでいるときで処理が違う
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// エフェクトの更新処理
    /// </summary>
    void UpdateEffect();
    /// <summary>
    /// カウントダウン終了までの処理
    /// </summary>
    void UpdatePreCountdownEnd();
    /// <summary>
    /// 遊んでいるときの処理
    /// </summary>
    void UpdatePlayGame();
    /// <summary>
    /// 全部回収後の処理
    /// </summary>
    void UpdatePoatGameEndProcess();
    //ゲーム中断機能
    Menu* menu;
    //ゴール後の処理
    PostGameEndStagingProcess* postGameEndProcess;
    //遊んでいるときの処理
    PlayGameProcess* playGameProcess;
    //レース前の処理
    PrePlayGameProcess* gamePrevProcess;
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
    /// <summary>
    /// プレイシーンの段階
    /// </summary>
    enum PlaySceneProgress
    {
        start,//最初の処理
        game,//遊んでいるときの処理
        postGameEnd,//ゴールし終わった時の処理
    };
    //今何の処理を行うか決める変数
    PlaySceneProgress nowProgress;
    //各シーンの処理の関数ポインタ
    void (PlayScene::* UpdateFunc[PlaySceneProcess])();
};