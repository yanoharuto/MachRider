#pragma once
#include <iostream>
#include <memory>
#include "SceneBase.h"

class Menu;
class EditorCameraObserver;
class EditorManager;
class EditManual;
class EditorEffect;
class EditorCamera;
/// <summary>
/// �ҏW�V�[���N���X
/// </summary>
class EditorScene final : public SceneBase
{
public:
    /// <summary>
    /// ���j���[��ʂ�J�����A�ҏW�N���X�Ȃǂ��m��
    /// </summary>
    EditorScene();
    /// <summary>
    /// �R���X�g���N�^�Ŋm�ۂ��������J��
    /// </summary>
    ~EditorScene()override;
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
    //�ҏW���̎�ނ�ύX����
    EditorManager* editManager;
    //�ҏW�������
    EditManual* manual;
    //�ҏW���ɏo�Ă���G�t�F�N�g�̍X�V��
    EditorEffect* editorEffect;
    //�J����
    std::shared_ptr<EditorCamera> camera;
    //�J�����̌�����ҏW�I�u�W�F�N�g�ɓ`����N���X
    std::shared_ptr<EditorCameraObserver> cameraObserver;
};