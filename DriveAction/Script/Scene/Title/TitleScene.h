#pragma once
#include "SceneBase.h"
/// <summary>
/// �^�C�g��
/// </summary>
class TitleScene final :
    public SceneBase
{
public:
    /// <summary>
    /// TitleSceneFlow���m��
    /// </summary>
    TitleScene();
    /// <summary>
    /// �^�C�g���ł̏���
    /// </summary>
    /// <returns>�Q�[���I����Editor���[�h��Play�V�[���ɑJ��</returns>
    SceneType Update();
private:
};

