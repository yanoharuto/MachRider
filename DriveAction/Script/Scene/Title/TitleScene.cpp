#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "TitleSceneFlow.h"
#include "FadeInFadeOut.h"
#include "UserInput.h"
/// <summary>
/// TitleSceneFlowを確保
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    sceneFlow = new TitleSceneFlow();
}
/// <summary>
/// タイトルでの処理
/// </summary>
/// <returns>ゲーム終了かEditorモードかPlayシーンに遷移</returns>
SceneType TitleScene::Update()
{
    //タイトルでの処理
    sceneFlow->Update();
    //タイトル処理終了ならゲーム画面へ
    if (sceneFlow->GetIsEndProcesss())
    {
        return SceneType::PLAY;
    }
    else
    {
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
}