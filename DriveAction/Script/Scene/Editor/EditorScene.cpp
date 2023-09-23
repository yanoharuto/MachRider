#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "Menu.h"
#include "EditorManager.h"
#include "UserInput.h"
#include "EditorCamera.h"
#include "EditorEffect.h"
#include "EditManual.h"
#include "CameraObserver.h"
/// <summary>
/// メニュー画面やカメラ、編集クラスなどを確保
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::editor)
{
    //カメラ
    camera = std::make_shared<EditorCamera>();
    cameraObserver = std::make_unique<CameraObserver>(camera);
    //編集オブジェクトの種類を変更するクラス
    editManager = new EditorManager();
    //メニュー画面
    menu = new Menu();
    //操作説明説明
    manual = new EditManual();
    //エフェクト
    editorEffect = new EditorEffect();
}
/// <summary>
/// コンストラクタで確保した物を開放
/// </summary>
EditorScene::~EditorScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(editManager);
    camera.reset();
    SAFE_DELETE(manual);
    SAFE_DELETE(editorEffect);
}
/// <summary>
/// メニューとEditorの更新
/// </summary>
/// <returns>タイトルに戻ったりゲームを終了したりEditorを再読み込みしたりする</returns>
SceneType EditorScene::Update()
{
    menu->Update();//メニュー画面の更新

    using enum Menu::MenuOptions;
    switch (menu->GetMenuState())
    {
        //メニューUIの選択ごとにシーンを新しく読み込む
    case retry:
        return SceneType::reload;//再読み込み
        break;
    case returnTitle:
        return SceneType::title;//タイトル
        break;
    case exitGame:
        return SceneType::escape;//ゲーム終了
        break;
    }
    //メニュー画面開いてなかったら
    if (!menu->IsMenuOpen())
    {
        if (UserInput::GetInputState(AKey) == Hold)
        {
            camera->UpdateDirectionAndTargetBetween();
        }
        else
        {
            //シーンごとの処理
            editManager->Update(cameraObserver);
        }

        //カメラの更新
        camera->UpdatePositionAndTarget(editManager->GetNowEditObjPlaceData());
        //エフェクト更新
        editorEffect->Update(editManager->GetNowEditObjPlaceData());
    }
    return nowSceneType;
}
/// <summary>
/// メニュー画面とEditorの描画
/// </summary>
void EditorScene::Draw() const
{
    //メニュー画面を開いていたら
    if (menu->IsMenuOpen())
    {
        menu->Draw();
    }
    else
    {
        editManager->Draw(cameraObserver);
        //今編集している稼動かで操作説明変更
        if(editManager->IsNowEdit())
        {
            //操作説明
            manual->DrawEditManualString();
        }
        else
        {
            manual->DrawSelectManualString();
        }
    }
}
