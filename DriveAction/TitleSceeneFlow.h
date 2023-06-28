#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"
class RaceScreen;
class StageSelect;
class StageInitializer;
class SpaceKeyUI;
class TitleCamera;
class TitleDemo;
class Timer;
/// <summary>
/// タイトルシーンの処理の流れ
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow()override;
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
    /// <param name="changedState">タイトルシーンを変更する先</param>
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
    SpaceKeyUI* spaceKeyUI;
    //タイトルの後ろで走らせる
    TitleDemo* titleDemo;
    //タイトルの状態
    TitleState titleState;
    //描画した状態を保存する
    RaceScreen* screen;
    //タイトルロゴの
    UIData titleLogoData;
};