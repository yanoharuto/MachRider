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
#include "EditManual.h"
#include "EditorEffect.h"
/// <summary>
/// 編集に必要なものを確保
/// </summary>
EditorSceneFlow::EditorSceneFlow()
{
    //背景
    stage = new StageObjectController();
    editState = editPlayer;
    //各オブジェクトのEditor
    editorVec.push_back(new PlayerDataEditor());
    editorVec.push_back(new CollectItemDataEditor());
    editorVec.push_back(new EnemyDataEditor(saw));
    editorVec.push_back(new EnemyDataEditor(moveSaw));
    editorVec.push_back(new EnemyDataEditor(circleLaserShip));
    editorVec.push_back(new EnemyDataEditor(upDownLaserShip));
    editorVec.push_back(new EnemyDataEditor(bomberShip));
    //カメラ
    camera = new EditorCamera();
    camera->Update();
    //とりあえずタイトルに戻るようにする
    nextSceneType=SceneType::TITLE;
    //現在の編集クラス
    nowEditor = editorVec[0];
    //操作説明説明
    manual = new EditManual();
    //エフェクト
    editorEffect = new EditorEffect();
}
/// <summary>
/// 編集物やステージの背景などを解放
/// </summary>
EditorSceneFlow::~EditorSceneFlow()
{
    SAFE_DELETE(stage);
    SAFE_DELETE(manual);
    SAFE_DELETE(editorEffect);
    for (int i = 0; i < editorVec.size(); i++)
    {
        SAFE_DELETE(editorVec[i]);
    }
    SAFE_DELETE(camera);
}
/// <summary>
/// 更新
/// </summary>
void EditorSceneFlow::Update()
{
    //カメラの更新
    camera->Update();
    //Skeyで出てくるタイミングを変更
    if (UserInput::GetInputState(SKey) == Hold)
    {
        nowEditor->ChangeEditedCollectNum();
    }
    //sとaKeyを押してない間は編集
    else if (UserInput::GetInputState(AKey) != Hold)
    {
        //今なにも編集していないなら
        if (nowEditor->IsEndEditing())
        {
            //編集するオブジェクトの種類を変更
            SelectEditKind();
        }
        //編集
        nowEditor->Update();
    }

    //エフェクト更新
    editorEffect->Update(nowEditor);
    Effekseer_Sync3DSetting();
    //エフェクト更新
    UpdateEffekseer3D();
}
/// <summary>
/// 描画
/// </summary>
void EditorSceneFlow::Draw() const
{
    //ステージに配置されている物
    stage->Draw();
    //各オブジェクトの描画
    for (int i = 0; i < editorVec.size(); i++)
    {
        editorVec[i]->Draw();
    }
    //操作説明
    manual->Draw(nowEditor);
    //エフェクト
    DrawEffekseer3D();
}
/// <summary>
/// 次に何を編集するか選択する
/// </summary>
void EditorSceneFlow::SelectEditKind()
{
    //上下キーで編集できるオブジェクトの種類を変更
    if (UserInput::GetInputState(Up) == Push) 
    {
        selectEditorNum--;
        //一周したら後ろに繋げる
        if (selectEditorNum < 0)
        {
            selectEditorNum = editorVec.size() - 1;
        }
    }
    else if (UserInput::GetInputState(Down) == Push)
    {
        selectEditorNum++;
        //一周したら一番前に繋げる
        if (selectEditorNum > editorVec.size() - 1)
        {
            selectEditorNum = 0;
        }
    }
    //現在編集中のエディターを更新
    nowEditor = editorVec[selectEditorNum];
}