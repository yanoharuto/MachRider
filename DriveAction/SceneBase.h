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
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase();
    /// <summary>
    /// �V�[���̍X�V
    /// </summary>
    /// <returns></returns>
    virtual SceneType Update();
    
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() const;
    
protected:
    //���̃V�[���̎��
    SceneType nowSceneType;
    //�V�[���̏����̗���
    SceneFlowBase* sceneFlow;
};