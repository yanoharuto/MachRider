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
/// 車とかフェードインフェードアウトクラスの確保
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
/// 車とかフェードインフェードアウトクラスのDelete
/// </summary>
TitleSceneFlow::~TitleSceneFlow()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(spaceKeyUI);
    SAFE_DELETE(titleDemo);
    SAFE_DELETE(titleScore);
}
/// <summary>
/// 更新
/// </summary>
void TitleSceneFlow::Update()
{
    //車が勝手に動いたりする
    titleDemo->Update();

    //BGM長しっぱ
    if (!SoundPlayer::IsPlaySound(titleBGM)&&titleState!=TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //状況によってやるべき処理を変更
    switch (titleState)
    {
    case TitleSceneFlow::TitleState::waitSpaceKey:
        WaitPressSpaceKey();//スペースキー待ち
        break;
    case TitleSceneFlow::TitleState::stageSelect:
        SelectStageProcess();//ステージ選択
        break;
    case TitleSceneFlow::TitleState::processEnd:
        EndTitleProcess();//処理終了
        break;
    default:
        break;
    }
}
/// <summary>
/// ステージ選択とかロゴとかの描画
/// </summary>
void TitleSceneFlow::Draw()const
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
        titleScore->Draw();
    }
    screen->ScreenUpdate();
}
/// <summary>
/// スペースキーを押したらtitleStateを変更
/// </summary>
/// <param name="changedState">変更先の状態</param>
void TitleSceneFlow::OnPressSpaceKeyProcess(TitleState changedState)
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
void TitleSceneFlow::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// ステージ選択処理
/// </summary>
void TitleSceneFlow::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
/// <summary>
/// タイトルシーン終了処理
/// </summary>
void TitleSceneFlow::EndTitleProcess()
{
    SoundPlayer::StopSound(titleBGM);
    isEndProcesss = true;
    nextSceneType = SceneType::PLAY;
}
