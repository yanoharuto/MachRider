#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"
#include "StageObjectController.h"
class GameScreen;
class StageSelect;
class CollectItemObserver;
class FlashUI;
class TitleCamera;
class TitleObject;
class Timer;
class TitleRanking;
/// <summary>
/// �^�C�g���V�[���̏����̗���
/// </summary>
class TitleSceneFlow :public SceneFlowBase
{
public:
    /// <summary>
    /// �ԂƂ��t�F�[�h�C���t�F�[�h�A�E�g�N���X�̊m��
    /// </summary>
    TitleSceneFlow();
    /// <summary>
    /// �ԂƂ��t�F�[�h�C���t�F�[�h�A�E�g�N���X��Delete
    /// </summary>
    ~TitleSceneFlow()override;
    /// <summary>
    /// �X�V
    /// </summary>
    void Update() override;
    /// <summary>
    /// �X�e�[�W�I���Ƃ����S�Ƃ��̕`��
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// �^�C�g���̏��
    /// </summary>
    enum class TitleState
    {
        //�X�y�[�X�L�[�������O�̏��
        waitSpaceKey,
        //�X�e�[�W�̑I��
        stageSelect,
        //�^�C�g���V�[���ł̏����I��
        processEnd
    };
    /// <summary>
    /// �X�y�[�X�L�[����������titleState��ύX
    /// </summary>
    /// <param name="c
    /// edState">�^�C�g���V�[����ύX�����</param>
    void OnPressSpaceKeyProcess(TitleState changedState);
    /// <summary>
    /// �X�y�[�X�L�[�������̂�҂�
    /// </summary>
    void WaitPressSpaceKey();
    /// <summary>
    /// �X�e�[�W�I������
    /// </summary>
    void SelectStageProcess();
    /// <summary>
    /// �^�C�g���V�[���I������
    /// </summary>
    void EndTitleProcess();
    //�X�e�[�W�̏��
    StageSelect* stageSelect;
    //�X�y�[�X�L�[�������Ă��炤���߂�UI
    FlashUI* spaceKeyUI;
    //�^�C�g���̌��ő��点��
    TitleObject* titleObject;
    //�^�C�g���̏��
    TitleState titleState;
    //�`�悵����Ԃ�ۑ�����
    GameScreen* screen;
    //�^�C�g�����S
    UIData titleLogoData;
    //�^�C�g����ʂɕ\������n�C�X�R�A
    TitleRanking* titleScore;
};