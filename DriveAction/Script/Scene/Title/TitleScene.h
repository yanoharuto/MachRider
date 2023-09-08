#pragma once
#include "SceneBase.h"
#include "UIManager.h"
class GameScreen;
class StageSelect;
class FlashUI;
class TitleCamera;
class TitleObject;
class TitleRanking;
/// <summary>
/// �^�C�g��
/// </summary>
class TitleScene final : public SceneBase
{
public:
    /// <summary>
    /// TitleSceneFlow���m��
    /// </summary>
    TitleScene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TitleScene()override;
    /// <summary>
    /// �^�C�g���ł̏���
    /// </summary>
    /// <returns>�Q�[���I����Editor���[�h��Play�V�[���ɑJ��</returns>
    SceneType Update()override;
    /// <summary>
    /// �X�e�[�W�I����X�R�A�̃����L���O�A���ő���Ԃ�`��
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
    //�X�e�[�W�̏��
    StageSelect* stageSelect;
    //�X�y�[�X�L�[�������Ă��炤���߂�UI
    FlashUI* spaceKeyUI;
    //�^�C�g���̌��ő��点��
    TitleObject* titleObject;
    //�`�悵����Ԃ�ۑ�����
    GameScreen* screen;
    //�^�C�g����ʂɕ\������n�C�X�R�A
    TitleRanking* titleScore;
    //�^�C�g�����S
    UIData titleLogoUI;
    //�^�C�g���̏��
    TitleState titleState;
};