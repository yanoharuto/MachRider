#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"
#include "StageObjectController.h"
class GameScreen;
class StageSelect;
class CollectItemObserver;
class FlashUI;
class TitleCamera;
class TitleObject;
class Timer;
class TitleRanking;
/// <summary>
/// タイトルシーンの処理の流れ
/// </summary>
class TitleSceneFlow :public SceneFlowBase
{
public:
    /// <summary>
    /// 車とかフェードインフェードアウトクラスの確保
    /// </summary>
    TitleSceneFlow();
    /// <summary>
    /// 車とかフェードインフェードアウトクラスのDelete
    /// </summary>
    ~TitleSceneFlow()override;
    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;
    /// <summary>
    /// ステージ選択とかロゴとかの描画
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// タイトルの状態
    /// </summary>
    enum class TitleState
    {
        //スペースキーを押す前の状態
        waitSpaceKey,
        //ステージの選択
        stageSelect,
        //タイトルシーンでの処理終了
        processEnd
    };
    /// <summary>
    /// スペースキーを押したらtitleStateを変更
    /// </summary>
    /// <param name="c
    /// edState">タイトルシーンを変更する先</param>
    void OnPressSpaceKeyProcess(TitleState changedState);
    /// <summary>
    /// スペースキーを押すのを待つ
    /// </summary>
    void WaitPressSpaceKey();
    /// <summary>
    /// ステージ選択処理
    /// </summary>
    void SelectStageProcess();
    /// <summary>
    /// タイトルシーン終了処理
    /// </summary>
    void EndTitleProcess();
    //ステージの情報
    StageSelect* stageSelect;
    //スペースキーを押してもらうためのUI
    FlashUI* spaceKeyUI;
    //タイトルの後ろで走らせる
    TitleObject* titleObject;
    //タイトルの状態
    TitleState titleState;
    //描画した状態を保存する
    GameScreen* screen;
    //タイトルロゴ
    UIData titleLogoData;
    //タイトル画面に表示するハイスコア
    TitleRanking* titleScore;
};