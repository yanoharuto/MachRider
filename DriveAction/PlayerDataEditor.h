#pragma once
#include "StageDataEditor.h"
/// <summary>
/// �v���C���[�̏����ʒu�̕ҏW
/// </summary>
class PlayerDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
    /// �v���C���[�̏����ʒu�̕ҏW
    /// </summary>
    PlayerDataEditor();
    ~PlayerDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �v���C���[�̕`��
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// �v���C���[�̕`��
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// ������`��
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// �I������Ă���Ƃ��̕�����`��
    /// </summary>
    void DrawSelectString()const override;
private:
    //�v���C���[
    EditorObject* player;
    const int drawStrY = 400;
    unsigned int selectColor = GetColor(255, 0, 0);
    std::string drawEditString = "Player";
};

