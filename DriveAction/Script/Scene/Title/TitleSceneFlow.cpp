#include "TitleSceneFlow.h"
#include "Utility.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "SpaceKeyUI.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
#include "TitleDemo.h"
#include "Timer.h"
#include "GameScreen.h"
#include "UIDrawer.h"
#include "TitleRanking.h"
/// <summary>
/// �ԂƂ��t�F�[�h�C���t�F�[�h�A�E�g�N���X�̊m��
/// </summary>
TitleSceneFlow::TitleSceneFlow()
{
    SoundPlayer::LoadSound(titleBGM);
    stageSelect = new StageSelect();  
    spaceKeyUI = new FlashUI(titlePressSpaceKey);
    titleDemo = new TitleDemo();
    titleScore = new TitleRanking();
    titleLogoData = UIManager::CreateUIData(tilteLogo);
    
    SoundPlayer::LoadSound(sceneNextSE);
}
/// <summary>
/// �ԂƂ��t�F�[�h�C���t�F�[�h�A�E�g�N���X��Delete
/// </summary>
TitleSceneFlow::~TitleSceneFlow()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(spaceKeyUI);
    SAFE_DELETE(titleDemo);
    SAFE_DELETE(titleScore);
}
/// <summary>
/// �X�V
/// </summary>
void TitleSceneFlow::Update()
{
    //�Ԃ�����ɓ������肷��
    titleDemo->Update();

    //BGM��������
    if (!SoundPlayer::IsPlaySound(titleBGM)&&titleState!=TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //�󋵂ɂ���Ă��ׂ�������ύX
    switch (titleState)
    {
    case TitleSceneFlow::TitleState::waitSpaceKey:
        WaitPressSpaceKey();//�X�y�[�X�L�[�҂�
        break;
    case TitleSceneFlow::TitleState::stageSelect:
        SelectStageProcess();//�X�e�[�W�I��
        break;
    case TitleSceneFlow::TitleState::processEnd:
        EndTitleProcess();//�����I��
        break;
    default:
        break;
    }
}
/// <summary>
/// �X�e�[�W�I���Ƃ����S�Ƃ��̕`��
/// </summary>
void TitleSceneFlow::Draw()const
{
    titleDemo->Draw();
    UIDrawer::DrawRotaUI(titleLogoData, 0, 0,true);
    if (titleState == TitleState::waitSpaceKey)
    {
        spaceKeyUI->Draw();//�X�y�[�X�L�[�҂�UI
    }
    else
    {
        stageSelect->Draw();//�X�e�[�W�I��UI
        titleScore->Draw();
    }
    screen->ScreenUpdate();
}
/// <summary>
/// �X�y�[�X�L�[����������titleState��ύX
/// </summary>
/// <param name="changedState">�ύX��̏��</param>
void TitleSceneFlow::OnPressSpaceKeyProcess(TitleState changedState)
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
void TitleSceneFlow::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// �X�e�[�W�I������
/// </summary>
void TitleSceneFlow::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
/// <summary>
/// �^�C�g���V�[���I������
/// </summary>
void TitleSceneFlow::EndTitleProcess()
{
    SoundPlayer::StopSound(titleBGM);
    isEndProcesss = true;
    nextSceneType = SceneType::PLAY;
}
