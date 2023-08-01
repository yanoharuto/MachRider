#pragma once

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
    virtual void Draw() const;
    
protected:
    //このシーンの種類
    SceneType nowSceneType;
    //シーンの処理の流れ
    SceneFlowBase* sceneFlow;
};