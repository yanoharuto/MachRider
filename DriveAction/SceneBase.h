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
    virtual void Draw();
    
protected:
    void DeleteUniquePtr();
    //���̃V�[���̎��
    SceneType nowSceneType;
    //�t�F�[�h�C���t�F�[�h�A�E�g
    FadeInFadeOut* fadeInFadeOut;
    //�V�[���̏����̗���
    SceneFlowBase* sceneFlow;
    //�^�C�}�[
    std::unique_ptr <Clock*> clock;
    std::unique_ptr<EffectManager*> effectManager;
    std::unique_ptr <SoundPlayer*> soundPlayer;
    std::unique_ptr <InitActor*> initActor;
    std::unique_ptr <UIManager*> uiManager;
};