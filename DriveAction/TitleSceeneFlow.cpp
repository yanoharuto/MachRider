#include "TitleSceeneFlow.h"
#include "Utility.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "SpaceKeyUI.h"
#include "SoundPlayer.h"
#include "UIManager.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
#include "TitleDemo.h"
#include "Timer.h"
#include "RaceScreen.h"
#include "UIDrawer.h"

TitleSceeneFlow::TitleSceeneFlow()
{
    stageSelect = new StageSelect();  
    spaceKeyUI = new FlashUI(titlePressSpaceKey);
    titleDemo = new TitleDemo();
    
    titleLogoData = UIManager::CreateUIData(tilteLogo);
    
    SoundPlayer::LoadSound(sceneNextSE);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(spaceKeyUI);
    SAFE_DELETE(titleDemo);
}

void TitleSceeneFlow::Update()
{
    titleDemo->Update();

    //BGM��������
    if (!SoundPlayer::IsPlaySound(titleBGM)&&titleState!=TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //�󋵂ɂ���Ă��ׂ�������ύX
    switch (titleState)
    {
    case TitleSceeneFlow::TitleState::waitSpaceKey:
        WaitPressSpaceKey();
        break;
    case TitleSceeneFlow::TitleState::stageSelect:
        SelectStageProcess();
        break;
    case TitleSceeneFlow::TitleState::processEnd:
        EndTitleProcess();
        break;
    default:
        break;
    }
    
    //�G�X�P�[�v�L�[����������I��
    if (UserInput::GetInputState(EscapeKey)==Push)
    {
        isEndProccess = true;
        nextSceneType = SceneType::ESCAPE;
    }
}
/// <summary>
/// �X�e�[�W�I���Ƃ����S�Ƃ��̕`��
/// </summary>
void TitleSceeneFlow::Draw()const
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
    }
    screen->ScreenUpdate();
}
/// <summary>
/// �X�y�[�X�L�[����������titleState��ύX
/// </summary>
/// <param name="changedState">�ύX��̏��</param>
void TitleSceeneFlow::OnPressSpaceKeyProcess(TitleState changedState)
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
void TitleSceeneFlow::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// �X�e�[�W�I������
/// </summary>
void TitleSceeneFlow::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
/// <summary>
/// �^�C�g���V�[���I������
/// </summary>
void TitleSceeneFlow::EndTitleProcess()
{
    SoundPlayer::StopSound(titleBGM);
    isEndProccess = true;
    nextSceneType = SceneType::PLAY;
}
