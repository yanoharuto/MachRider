#pragma once
#include <iostream>
#include "SceneType.h"

class FadeInFadeOut;
class SceneFlowBase;
class Clock;
class SoundPlayer;
class InitActor;
class EffectManager;
class UIManager;
class SceneBase abstract
{
public:
    SceneBase(SceneType _SceneType);
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase();
    /// <summary>
    /// シーンの更新
    /// </summary>
    /// <returns></returns>
    virtual SceneType Update();
    
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw();
    
protected:
    void DeleteUniquePtr();
    //このシーンの種類
    SceneType nowSceneType;
    //フェードインフェードアウト
    FadeInFadeOut* fadeInFadeOut;
    //シーンの処理の流れ
    SceneFlowBase* sceneFlow;
    //タイマー
    std::unique_ptr <Clock*> clock;
    std::unique_ptr<EffectManager*> effectManager;
    std::unique_ptr <SoundPlayer*> soundPlayer;
    std::unique_ptr <InitActor*> initActor;
    std::unique_ptr <UIManager*> uiManager;
};