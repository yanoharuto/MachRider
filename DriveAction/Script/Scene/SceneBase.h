#pragma once

#include "SceneType.h"

class FadeInFadeOut;
class SceneFlowBase;
class Clock;
class SoundPlayer;
class InitActor;
class EffectManager;
class UIManager;
/// <summary>
/// 各シーンの分岐を渡す
/// </summary>
class SceneBase abstract
{
public:
    /// <summary>
    /// 現在のシーンの保存
    /// </summary>
    /// <param name="_SceneType">現在のシーンの保存</param>
    SceneBase(SceneType _SceneType);    
    /// <summary>
    /// SceneFlowの解放
    /// </summary>
    virtual ~SceneBase();
    /// <summary>
    /// シーンの更新
    /// </summary>
    /// <returns>次のシーン</returns>
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