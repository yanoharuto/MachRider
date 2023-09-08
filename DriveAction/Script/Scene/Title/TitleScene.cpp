#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "FadeInFadeOut.h"
#include "UserInput.h"
#include "StageSelect.h"
#include "SpaceKeyUI.h"
#include "TitleObject.h"
#include "Timer.h"
#include "GameScreen.h"
#include "UIDrawer.h"
#include "TitleRanking.h"

/// <summary>
/// �ԂƂ��t�F�[�h�C���t�F�[�h�A�E�g�N���X�̊m��
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    SoundPlayer::LoadAndInitSound(titleBGM);
    stageSelect = new StageSelect();
    spaceKeyUI = new FlashUI(titlePressSpaceKey);
    titleObject = new TitleObject();
    titleScore = new TitleRanking();
    titleLogoUI = UIManager::CreateUIData(tilteLogo);

    SoundPlayer::LoadAndInitSound(sceneNextSE);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(spaceKeyUI);
    SAFE_DELETE(titleObject);
    SAFE_DELETE(titleScore);
}
/// <summary>
/// �^�C�g���ł̏���
/// </summary>
/// <returns>�Q�[���I����Editor���[�h��Play�V�[���ɑJ��</returns>
SceneType TitleScene::Update()
{
    //�^�C�g���ł̏���//�Ԃ�����ɓ������肷��
    titleObject->Update();

    //BGM��������
    if (!SoundPlayer::IsPlaySound(titleBGM) && titleState != TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //�󋵂ɂ���Ă��ׂ�������ύX
    switch (titleState)
    {
    case TitleScene::TitleState::waitSpaceKey:
        WaitPressSpaceKey();//�X�y�[�X�L�[�҂�
        break;
    case TitleScene::TitleState::stageSelect:
        SelectStageProcess();//�X�e�[�W�I��
        break;
    case TitleScene::TitleState::processEnd:
        SoundPlayer::StopSound(titleBGM);
        return SceneType::PLAY;//�����I��
        break;
    default:
        break;
    }

    //�G�X�P�[�v�L�[����������I��
    if (UserInput::GetInputState(EscapeKey) == Push)
    {
        return SceneType::ESCAPE;
    }
    //W�L�[��Editor���[�h
    else if (UserInput::GetInputState(WKey) == Push)
    {
        return SceneType::EDITOR;
    }
    return nowSceneType;
}
/// <summary>
/// �X�e�[�W�I����X�R�A�̃����L���O�A���ő���Ԃ�`��
/// </summary>
void TitleScene::Draw() const
{
    //�Ԃ�X�e�[�W��`��
    titleObject->Draw();
    //�^�C�g�����S�̕`��
    UIDrawer::DrawRotaUI(titleLogoUI, 0, 0, true);

    if (titleState == TitleState::waitSpaceKey)
    {
        spaceKeyUI->Draw();//�X�y�[�X�L�[�҂�UI
    }
    else
    {
        stageSelect->Draw();//�X�e�[�W�I��UI
        titleScore->Draw();
    }
    //�`����e�ۑ�
    screen->ScreenUpdate();
}
/// <summary>
/// �X�y�[�X�L�[����������titleState��ύX
/// </summary>
/// <param name="changedState">�ύX��̏��</param>
void TitleScene::OnPressSpaceKeyProcess(TitleState changedState)
{
    if (UserInput::GetInputState(Space) == Push)
    {
        SoundPlayer::Play2DSE(sceneNextSE);
        titleState = changedState;
    }
}
/// <summary>
/// �X�y�[�X�L�[�������̂�҂�
/// </summary>
void TitleScene::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// �X�e�[�W�I������
/// </summary>
void TitleScene::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
