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

    //BGM長しっぱ
    if (!SoundPlayer::IsPlaySound(titleBGM)&&titleState!=TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //状況によってやるべき処理を変更
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
    
    //エスケープキーを押したら終了
    if (UserInput::GetInputState(EscapeKey)==Push)
    {
        isEndProccess = true;
        nextSceneType = SceneType::ESCAPE;
    }
}
/// <summary>
/// ステージ選択とかロゴとかの描画
/// </summary>
void TitleSceeneFlow::Draw()const
{
    titleDemo->Draw();
    UIDrawer::DrawRotaUI(titleLogoData, 0, 0,true);
    if (titleState == TitleState::waitSpaceKey)
    {
        spaceKeyUI->Draw();//スペースキー待ちUI
    }
    else
    {
        stageSelect->Draw();//ステージ選択UI
    }
    screen->ScreenUpdate();
}
/// <summary>
/// スペースキーを押したらtitleStateを変更
/// </summary>
/// <param name="changedState">変更先の状態</param>
void TitleSceeneFlow::OnPressSpaceKeyProcess(TitleState changedState)
{
    if (UserInput::GetInputState(Space) == Push)
    {
        SoundPlayer::Play2DSE(sceneNextSE);
        titleState = changedState;
    }
}
/// <summary>
/// スペースキーを押すのを待つ
/// </summary>
void TitleSceeneFlow::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// ステージ選択処理
/// </summary>
void TitleSceeneFlow::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
/// <summary>
/// タイトルシーン終了処理
/// </summary>
void TitleSceeneFlow::EndTitleProcess()
{
    SoundPlayer::StopSound(titleBGM);
    isEndProccess = true;
    nextSceneType = SceneType::PLAY;
}
