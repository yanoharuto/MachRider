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
/// 車とかフェードインフェードアウトクラスの確保
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
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(spaceKeyUI);
    SAFE_DELETE(titleObject);
    SAFE_DELETE(titleScore);
}
/// <summary>
/// タイトルでの処理
/// </summary>
/// <returns>ゲーム終了かEditorモードかPlayシーンに遷移</returns>
SceneType TitleScene::Update()
{
    //タイトルでの処理//車が勝手に動いたりする
    titleObject->Update();

    //BGM長しっぱ
    if (!SoundPlayer::IsPlaySound(titleBGM) && titleState != TitleState::processEnd)
    {
        SoundPlayer::Play2DSE(titleBGM);
    }
    //状況によってやるべき処理を変更
    switch (titleState)
    {
    case TitleScene::TitleState::waitSpaceKey:
        WaitPressSpaceKey();//スペースキー待ち
        break;
    case TitleScene::TitleState::stageSelect:
        SelectStageProcess();//ステージ選択
        break;
    case TitleScene::TitleState::processEnd:
        SoundPlayer::StopSound(titleBGM);
        return SceneType::PLAY;//処理終了
        break;
    default:
        break;
    }

    //エスケープキーを押したら終了
    if (UserInput::GetInputState(EscapeKey) == Push)
    {
        return SceneType::ESCAPE;
    }
    //WキーでEditorモード
    else if (UserInput::GetInputState(WKey) == Push)
    {
        return SceneType::EDITOR;
    }
    return nowSceneType;
}
/// <summary>
/// ステージ選択やスコアのランキング、後ろで走る車を描画
/// </summary>
void TitleScene::Draw() const
{
    //車やステージを描画
    titleObject->Draw();
    //タイトルロゴの描画
    UIDrawer::DrawRotaUI(titleLogoUI, 0, 0, true);

    if (titleState == TitleState::waitSpaceKey)
    {
        spaceKeyUI->Draw();//スペースキー待ちUI
    }
    else
    {
        stageSelect->Draw();//ステージ選択UI
        titleScore->Draw();
    }
    //描画内容保存
    screen->ScreenUpdate();
}
/// <summary>
/// スペースキーを押したらtitleStateを変更
/// </summary>
/// <param name="changedState">変更先の状態</param>
void TitleScene::OnPressSpaceKeyProcess(TitleState changedState)
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
void TitleScene::WaitPressSpaceKey()
{
    spaceKeyUI->Update();
    OnPressSpaceKeyProcess(TitleState::stageSelect);
}
/// <summary>
/// ステージ選択処理
/// </summary>
void TitleScene::SelectStageProcess()
{
    stageSelect->Update();
    OnPressSpaceKeyProcess(TitleState::processEnd);
}
