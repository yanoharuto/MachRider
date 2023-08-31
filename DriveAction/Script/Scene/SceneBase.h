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
/// �e�V�[���̕����n��
/// </summary>
class SceneBase abstract
{
public:
    /// <summary>
    /// ���݂̃V�[���̕ۑ�
    /// </summary>
    /// <param name="_SceneType">���݂̃V�[���̕ۑ�</param>
    SceneBase(SceneType _SceneType);    
    /// <summary>
    /// SceneFlow�̉��
    /// </summary>
    virtual ~SceneBase();
    /// <summary>
    /// �V�[���̍X�V
    /// </summary>
    /// <returns>���̃V�[��</returns>
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