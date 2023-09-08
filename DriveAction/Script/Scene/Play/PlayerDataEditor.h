#pragma once
#include "StageDataEditor.h"
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
class PlayerDataEditor final: public StageDataEditor
{
public:
    /// <summary>
    /// �v���C���[�̏����ʒu�̕ҏW
    /// </summary>
    PlayerDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update(std::weak_ptr<EditorCameraObserver> cameraObserever)override;
    /// <summary>
    /// �ҏW���A�ҏW�ς݂̃v���C���[��`��
    /// </summary>
    void Draw()const override;
private:
    //�ǂݍ��ރv���C���[�̈ʒu��������������t�@�C���̃p�X
    static const std::string loadEditFilePath;
};

