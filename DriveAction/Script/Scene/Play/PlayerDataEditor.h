#pragma once
#include "StageDataEditor.h"
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
class PlayerDataEditor : public StageDataEditor
{
public:
    /// <summary>
    /// �v���C���[�̏����ʒu�̕ҏW
    /// </summary>
    PlayerDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �ҏW���A�ҏW�ς݂̃v���C���[��`��
    /// </summary>
    void Draw()const override;
private:
    //�ǂݍ��ރv���C���[�̈ʒu��������������t�@�C���̃p�X
    static const std::string loadEditFilePath;
};
