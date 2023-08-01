#pragma once
#include "StageDataEditor.h"
/// <summary>
/// ���W�A�C�e���̕ҏW�N���X
/// </summary>
class CollectItemDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
    /// ���W�A�C�e���̕ҏW�N���X
    /// </summary>
    CollectItemDataEditor();
    ~CollectItemDataEditor();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �ҏW�ς݂̃I�u�W�F�N�g��`��
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// ���ݕҏW���Ă��镨��`��
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// ������`��
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// �I������Ă���Ƃ��̕�����`��
    /// </summary>
    void DrawSelectString()const override;
private:
    /// <summary>
    /// �ҏW�����ߋ��̎��W�A�C�e�����ĕҏW�ł���悤�ɂ���
    /// </summary>
    void SelectEditedCollect();

    //�ҏW���̎��W�A�C�e��
    EditorObject* nowEditCollect;
    //�G�f�B�^�[�̖��O�̕`��ʒu
    const int drawStrY = 600;
    //�����ڂ̎��W�A�C�e���Ȃ̂��̈ʒu
    const int drawCollectNumY = 200;
    //���@���Ԗڂ̃~�b�V�������̈ʒu
    const int drawMissionNumY = 0;
    //�G�f�B�^�[���I�����ꂽ�Ƃ��̐F
    const unsigned int selectColor = GetColor(0, 115, 250);
    //�G�f�B�^�[�̖��O
    const std::string drawEditString = "Collect";
    //�ߋ��ɕҏW�������W�A�C�e����I������̂Ɏg��
    int selectEditedCollectNum = -1;
};

