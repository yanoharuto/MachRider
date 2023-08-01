#include "EditorSceneFlow.h"
#include "DxLib.h"
#include "Utility.h"
#include "UserInput.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "EnemyDataEditor.h"
#include "CollectItemDataEditor.h"
#include "PlayerDataEditor.h"
#include "EditorCamera.h"
#include "EffekseerForDXLib.h"
/// <summary>
/// 編集の流れ
/// </summary>
EditorSceneFlow::EditorSceneFlow()
{
    stage = new StageObjectController();
    editState = EditPlayer;
    enemyEditor = new EnemyDataEditor();
    playerEditor = new PlayerDataEditor();
    collectEditor = new CollectItemDataEditor();
    camera = new EditorCamera();
    nextSceneType=SceneType::TITLE;
    nowEditor = playerEditor;
    camera->Update();
    SetFontSize(fontSize);
}

EditorSceneFlow::~EditorSceneFlow()
{
    SAFE_DELETE(stage);
    SAFE_DELETE(enemyEditor);
    SAFE_DELETE(playerEditor);
    SAFE_DELETE(collectEditor);
    SAFE_DELETE(camera);
}
/// <summary>
/// 更新
/// </summary>
void EditorSceneFlow::Update()
{
    //カメラの更新
    camera->Update();
    if (UserInput::GetInputState(SKey) == Hold)
    {
        nowEditor->ChangeMissionNum();
    }
    //sとaKeyを押してない間は編集
    else if (UserInput::GetInputState(AKey) != Hold)
    {
        //編集
        nowEditor->Update();
        //編集したら次へ
        if (nowEditor->IsEndEditing())
        {
            SelectEditKind();
        }
    }
    //エフェクト更新
    Effekseer_Sync3DSetting();
    UpdateEffekseer3D();
}
/// <summary>
/// 描画
/// </summary>
void EditorSceneFlow::Draw() const
{
    //ステージに配置されている物
    stage->Draw();
    //編集したものを全部描画
    playerEditor->DrawAllEditedObject();
    collectEditor->DrawAllEditedObject();
    enemyEditor->DrawAllEditedObject();
    //現在編集している物
    nowEditor->DrawNowEditObject();
    //文字の描画
    playerEditor->DrawEditString();
    collectEditor->DrawEditString();
    enemyEditor->DrawEditString();
    nowEditor->DrawSelectString();
    DrawEffekseer3D();
}
/// <summary>
/// 次に何を編集するか
/// </summary>
void EditorSceneFlow::SelectEditKind()
{
    if (UserInput::GetInputState(Up) == Push) 
    {
        switch (editState)
        {
        case EditorSceneFlow::EditCollect:
            editState = EditPlayer;
            nowEditor = playerEditor;
            break;
        case EditorSceneFlow::EditEnemy:
            editState = EditCollect;
            nowEditor = collectEditor;
            break;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        switch (editState)
        {
        case EditorSceneFlow::EditCollect:
            editState = EditEnemy;
            nowEditor = enemyEditor;
            break;
        case EditorSceneFlow::EditPlayer:
            editState = EditCollect;
            nowEditor = collectEditor;
            break;
        }
    }
}
