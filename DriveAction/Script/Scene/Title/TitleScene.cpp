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
    :SceneBase(SceneType::title)
{
    //�X�e�[�W�I��
    stageSelect = new StageSelect();
    //UI�̏���
    spaceKeyUI = new FlashUI(UIKind::titlePressSpaceKey);
    titleObject = new TitleObject();
    titleScore = new TitleRanking();
    titleLogoUIData = UIManager::CreateUIData(UIKind::tilteLogo);
    //��������
    SoundPlayer::LoadAndInitSound(SoundKind::titleBGM);
    SoundPlayer::LoadAndInitSound(SoundKind::sceneNextSE);
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
    UIManager::DeleteUIGraph(&titleLogoUIData);
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
    if (!SoundPlayer::IsPlaySound(SoundKind::titleBGM) && titleState != TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(SoundKind::titleBGM);
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
        SoundPlayer::StopSound(SoundKind::titleBGM);
        return SceneType::play;//�����I��
        break;
    default:
        break;
    }

    //�G�X�P�[�v�L�[����������I��
    if (UserInput::GetInputState(UserInput::KeyInputKind::EscapeKey) == UserInput::InputState::Push)
    {
        return SceneType::escape;
    }
    //W�L�[��Editor���[�h
    else if (UserInput::GetInputState(UserInput::KeyInputKind::WKey) == UserInput::InputState::Push)
    {
        return SceneType::editor;
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
    UIDrawer::DrawRotaUI(titleLogoUIData, 0, 0, true);

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
    if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
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
