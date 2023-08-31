#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"
class Timer;
class ActorControllerManager;
class DemoCarController;
class TitleCamera;
class ObjectObserver;
class ShadowMap;
class ReusableTimer;
/// <summary>
/// タイトルの後ろで動かす
/// </summary>
class TitleDemo
{
public:
    /// <summary>
    /// タイトルでゲームの雰囲気を伝える
    /// </summary>
    TitleDemo();
    /// <summary>
    /// 初期化周期タイマーや走っている車などの解放
    /// </summary>
    ~TitleDemo();
    /// <summary>
    /// 車やステージ選択の更新
    /// </summary>
    void Update();
    /// <summary>
    /// 車やステージの描画
    /// </summary>
    void Draw()const;
private:
    //纏めて動かすマネージャー
    ActorControllerManager* manager;
    //とりあえず走っている車
    DemoCarController* demoCarController;
    //カメラ
    TitleCamera* camera;
    //このタイマーが切れると場面変換
    ReusableTimer* initTimer;
    //影
    ShadowMap* shadowMap;
    //影とカメラに渡す車のオブザーバ
    std::shared_ptr<ObjectObserver> demoObserver;
    //場面変換周期
    const float initTime = 15.0f;
    //場面変換速度
    const float fadeSpeed = 3;
    //fadeValueを増やすか減らすか
    bool isAValueIncrement = true;
    //場面変換地
    float fadeValue;
    //走っている車の初期位置
    const VECTOR demoCarFirstPos = { -3200,0,0 };
    //走っている車の初期向き
    const VECTOR demoCarFirstDir = { 1,0,0.1f };
};