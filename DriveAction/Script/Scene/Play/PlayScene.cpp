#include "PlayScene.h"
#include "Utility.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "PlayGameProcess.h"
#include "PostGameEndStagingProcess.h"
#include "PrePlayGameProcess.h"
#include "EffekseerForDXLib.h"
#include "GameCamera.h"
#include "GameScreen.h"
#include "ShadowMap.h"
#include "PlayerObserver.h"
#include "PlayerCarController.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "CameraObserver.h"
/// <summary>
/// メニュー画面とゲームの流れの確保と音をロード
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::play)
{
    
    //現在の処理
    nowProgress = PlaySceneProgress::start;
    //ゴール後の処理とプレイヤーが操作する処理はまだ呼ばない
    postGameEndProcess = nullptr;
    playGameProcess = nullptr;
    //衝突判定管理
    conflictManager = new ConflictManager();
    //収集アイテム
    std::shared_ptr<CollectItemController> collectController = std::make_shared<CollectItemController>();
    collectItemObserver = std::make_shared<CollectItemObserver>(collectController);
    //様々なオブジェクトの更新などをする
    controllerManager = std::make_shared<ActorControllerManager>(collectItemObserver);
    //収集アイテムを共有
    controllerManager->AddActorController(collectController);
    //共有し終わったので開放
    collectController.reset();
    //プレイヤー
    std::shared_ptr<PlayerCarController> playerController = std::make_shared<PlayerCarController>();
    //プレイヤーの情報を更新するオブザーバー
    playerObserver = playerController->CreatePlayerObserver();
    //プレイヤーを共有
    controllerManager->AddActorController(playerController);
    //解放
    playerController.reset();
    //ゴール前処理
    gamePrevProcess = new PrePlayGameProcess(collectItemObserver);
    //カメラ
    camera = std::make_shared<GameCamera>(playerObserver);
    cameraObserver = std::make_shared<CameraObserver>(camera);
    //影
    shadowMap = new ShadowMap(playerObserver);
    //描画するたび保存出来るクラス
    screen = new GameScreen();
    //カメラの処理
    camera->Update();
    //メニュー画面の開放
    menu = new Menu();
}
/// <summary>
/// メニューとゲームの開放
/// </summary>
PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(conflictManager);
    SAFE_DELETE(shadowMap);
    SAFE_DELETE(screen);
    SAFE_DELETE(postGameEndProcess);
    SAFE_DELETE(playGameProcess);
    SAFE_DELETE(gamePrevProcess);
    controllerManager.reset();
    camera.reset();
}
/// <summary>
/// ゲームを遊ぶ
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //メニューでプレイヤーが何を選んだか
    menu->Update();
    using enum Menu::MenuOptions;
    //メニューの状態によって次のシーンを変更    
    switch (menu->GetMenuState())
    {
        //ゲームをやり直す
    case retry:
        nowSceneType = SceneType::reload;
        break;
        //タイトルに戻る
    case returnTitle:
        nowSceneType = SceneType::title;
        break;
        //ゲーム終了
    case exitGame:
        nowSceneType = SceneType::escape;
        break;
    }

    //menu画面が開いてないなら普通の処理
    if (!menu->IsMenuOpen())
    {
        (this->*UpdateFunc[CAST_I(nowProgress)])();
    }
   
    return nowSceneType;
}
/// <summary>
/// メニューを開いている時と遊んでいるときで処理が違う
/// </summary>
void PlayScene::Draw()const
{
   (this->*DrawFunc[CAST_I(nowProgress)])();
}

/// <summary>
/// エフェクトの更新処理
/// </summary>
void PlayScene::UpdateEffect()
{
    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();
    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
    UpdateEffekseer2D();
}
/// <summary>
/// カウントダウン終了までの処理
/// </summary>
void PlayScene::UpdatePreStartCountdownEnd()
{
    gamePrevProcess->Update();
    controllerManager->PrepareGame();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //エフェクトの更新
    UpdateEffect();
    //処理が終わったら
    if (gamePrevProcess->IsEndProcess())
    {
        nowProgress = PlaySceneProgress::game;
        SAFE_DELETE(gamePrevProcess);
        playGameProcess = new PlayGameProcess(playerObserver, collectItemObserver);
    }
}
/// <summary>
/// 遊んでいるときの処理
/// </summary>
void PlayScene::UpdatePlayGame()
{
    //ゲームを遊んでいるときの処理
    playGameProcess->Update(collectItemObserver);
    controllerManager->Update();
    conflictManager->Update();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //エフェクトの更新
    UpdateEffect();
    //遊んでいるときの処理が終了したら
    if (playGameProcess->IsEndProcess())
    {
        postGameEndProcess = new PostGameEndStagingProcess(playerObserver, playGameProcess->GetGameTimer());
        SAFE_DELETE(playGameProcess);
        controllerManager.reset();
        nowProgress = PlaySceneProgress::postGameEnd;
    }
}
/// <summary>
/// 全部回収後の処理
/// </summary>
void PlayScene::UpdatePostGameEndProcess()
{
    postGameEndProcess->Update();
    //エフェクトの更新
    UpdateEffect();
    if (postGameEndProcess->IsEndProcess())
    {
        nowSceneType = SceneType::title;
    }
}
/// <summary>
/// カウントダウン終了までの描画
/// </summary>
void PlayScene::DrawPreStartCountdownEnd()const
{
    if (menu->IsMenuOpen())//メニューを開いていたらメニュー画面を描画
    {
        menu->Draw();
    }
    else//遊んでいるときの状態を描画
    {
        controllerManager->Draw(cameraObserver);
        //エフェクト
        DrawEffekseer3D();
        DrawEffekseer2D();
        gamePrevProcess->Draw();
        //描画を保存
        screen->ScreenUpdate();
    }
}
/// <summary>
/// 遊んでいるときの描画
/// </summary>
void PlayScene::DrawPlayGame()const
{
    if (menu->IsMenuOpen())//メニューを開いていたらメニュー画面を描画
    {
        menu->Draw();
    }
    else//遊んでいるときの状態を描画
    {
        controllerManager->Draw(cameraObserver);
        //エフェクト
        DrawEffekseer3D();
        DrawEffekseer2D();
        playGameProcess->Draw();
        //描画を保存
        screen->ScreenUpdate();
    }
}
/// <summary>
/// 全部アイテムを回収した後の処理
/// </summary>
void PlayScene::DrawPostGameEndProcess()const
{
    if (menu->IsMenuOpen())//メニューを開いていたらメニュー画面を描画
    {
        menu->Draw();
    }
    else
    {
        //エフェクト
        DrawEffekseer3D();
        DrawEffekseer2D();
        postGameEndProcess->Draw();
    }
}