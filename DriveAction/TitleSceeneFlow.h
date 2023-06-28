#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "UIManager.h"
class RaceScreen;
class StageSelect;
class StageInitializer;
class SpaceKeyUI;
class TitleCamera;
class TitleDemo;
class Timer;
/// <summary>
/// �^�C�g���V�[���̏����̗���
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow()override;
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
    /// <param name="changedState">�^�C�g���V�[����ύX�����</param>
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
    SpaceKeyUI* spaceKeyUI;
    //�^�C�g���̌��ő��点��
    TitleDemo* titleDemo;
    //�^�C�g���̏��
    TitleState titleState;
    //�`�悵����Ԃ�ۑ�����
    RaceScreen* screen;
    //�^�C�g�����S��
    UIData titleLogoData;
};