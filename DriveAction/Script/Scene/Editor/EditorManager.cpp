#include "EditorManager.h"
#include "DxLib.h"
#include "Utility.h"
#include "UserInput.h"
#include "StageObjectController.h"
#include "StageDataEditor.h"
#include "EnemyDataEditor.h"
#include "CollectItemDataEditor.h"
#include "PlayerDataEditor.h"
#include "EffekseerForDXLib.h"
#include "EditManual.h"
#include "EditorEffect.h"
#include "CameraObserver.h"

/// <summary>
/// 編集に必要なものを確保
/// </summary>
EditorManager::EditorManager()
{
    //背景
    stage = new StageObjectController();
    using enum InitObjKind;
    //各オブジェクトのEditor
    editorVec.push_back(std::make_shared<PlayerDataEditor>());
    editorVec.push_back(std::make_shared<CollectItemDataEditor>());
    editorVec.push_back(std::make_shared<EnemyDataEditor>(saw));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(moveSaw));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(circleLaserShip));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(upDownLaserShip));
    editorVec.push_back(std::make_shared<EnemyDataEditor>(bomberShip));
    //現在の編集クラス
    nowEditor = editorVec[0];
}
/// <summary>
/// 編集物やステージの背景などを解放
/// </summary>
EditorManager::~EditorManager()
{
    SAFE_DELETE(stage);
    for (unsigned int i = 0; i < editorVec.size(); i++)
    {
        editorVec[i].reset();
    }
}
/// <summary>
/// 編集する種類や各編集物の編集
/// </summary>
void EditorManager::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //skeyで出てくるタイミングを変更
    if (UserInput::GetInputState(SKey) == Hold)
    {
        nowEditor->ChangeEditedCollectNum();
    }
    else//sとaKeyを押してない間は編集
    {
        //今なにも編集していないなら
        if (nowEditor->IsEndEditing())
        {
            //編集するオブジェクトの種類を変更
            SelectEditKind();
        }
        //編集
        nowEditor->Update(cameraObserever);
    }
}
/// <summary>
/// 描画
/// </summary>
void EditorManager::Draw(std::weak_ptr<CameraObserver> cameraObserever) const
{
    //ステージに配置されている物
    stage->Draw(cameraObserever);
    //各オブジェクトの描画
    for (unsigned int i = 0; i < editorVec.size(); i++)
    {
        editorVec[i]->Draw();
    }
    //エフェクト
    DrawEffekseer3D();
}
/// <summary>
/// 編集中かどうかを返す
/// </summary>
/// <returns>編集中ならTrue</returns>
bool EditorManager::IsNowEdit() const
{
    return nowEditor->IsNowEdit();
}
/// <summary>
/// 編集物の位置や向きを共有
/// </summary>
PlacementData EditorManager::GetNowEditObjPlaceData() const
{
    return nowEditor->GetEditObjPlacementData();
}
/// <summary>
/// 次に何を編集するか選択する
/// </summary>
void EditorManager::SelectEditKind()
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
        if (selectEditorNum > static_cast<int>(editorVec.size() - 1))
        {
            selectEditorNum = 0;
        }
    }
    //現在編集中のエディターを更新
    nowEditor = editorVec[selectEditorNum];
}