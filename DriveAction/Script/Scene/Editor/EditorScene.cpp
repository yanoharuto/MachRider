#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"
#include "UserInput.h"
/// <summary>
/// 編集シーンの流れをNew
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
    menu = new Menu();
}
/// <summary>
/// メニューとEditorの更新
/// </summary>
/// <returns>タイトルに戻ったりゲームを終了したりEditorを再読み込みしたりする</returns>
SceneType EditorScene::Update()
{
    menu->Update();
    switch (menu->GetMenuState())
    {
    case continueGame:
        //メニュー画面開いてなかったら
        if (!menu->IsMenuOpen())
        {
            //シーンごとの処理
            sceneFlow->Update();
        }
        break;
        //メニューUIの選択ごとに変更
    case retry:
        return SceneType::RELOAD;//再読み込み
        break;
    case returnTitle:
        return SceneType::TITLE;//タイトル
        break;
    case exitGame:
        return SceneType::ESCAPE;//ゲーム終了
        break;
    default:
        break;
    }
    return nowSceneType;
}
/// <summary>
/// メニュー画面とEditorの描画
/// </summary>
void EditorScene::Draw() const
{
    if (menu->IsMenuOpen())
    {
        menu->Draw();
    }
    else
    {
        sceneFlow->Draw();
    }
}
