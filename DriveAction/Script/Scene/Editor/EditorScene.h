#pragma once
#include "SceneBase.h"
#include "Menu.h"
/// <summary>
/// �ҏW�V�[���N���X
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// �ҏW�V�[���̗����New
    /// </summary>
    EditorScene();
    /// <summary>
    /// ���j���[��Editor�̍X�V
    /// </summary>
    /// <returns>�^�C�g���ɖ߂�����Q�[�����I��������Editor���ēǂݍ��݂����肷��</returns>
    SceneType Update()override;
    /// <summary>
    /// ���j���[��ʂ�Editor�̕`��
    /// </summary>
    void Draw()const override;
private:
    //���j���[
    Menu* menu;
};

