#pragma once
#include "SceneBase.h"
class Menu;
/// <summary>
/// �Q�[����V�ԃV�[��
/// </summary>
class PlayScene final:
    public SceneBase
{
public:
    /// <summary>
    /// ���j���[��ʂƃQ�[���̗���̊m�ۂƉ������[�h
    /// </summary>
    PlayScene();
    /// <summary>
/// ���j���[�ƃQ�[���̊J���Ɖ����~�߂�
/// </summary>
    ~PlayScene() override;
    /// <summary>
    /// �Q�[����V��
    /// </summary>
    /// <returns></returns>
    SceneType Update() override;
    /// <summary>
    /// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
    /// </summary>
    void Draw()const override;
private:
    //�ꎞ��~�����胊�g���C����p
    Menu* menu;
};