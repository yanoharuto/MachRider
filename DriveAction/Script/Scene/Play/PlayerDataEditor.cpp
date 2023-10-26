#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
//読み込むプレイヤーの位置や向きが入ったファイルのパス
const std::string PlayerDataEditor::loadFileName = "playerData";
/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(loadFileName,InitObjKind::player)
{
    if (!editedPlacementDataVec.empty())//ファイルが空じゃなかったら編集オブジェクトに位置を渡す
    {
        editObject->SetArrangementData(editedPlacementDataVec[0]);
    }
}

/// <summary>
/// 更新
/// </summary>
void PlayerDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    if (nowEditAction == EditActionKind::select && UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        //スペースキーで編集開始
        nowEditAction = EditActionKind::edit;
    }
    else if (nowEditAction == EditActionKind::edit)
    {
        //移動回転
        editObject->Update(cameraObserever);
        //編集終了
        if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            nowEditAction = EditActionKind::select;
            PlacementData editData = editObject->GePlacementData();
            editData.objKind = CAST_I(editKind);
            //プレイヤーは一つだけなので先頭のみ
            if(editedPlacementDataVec.empty())
            {
                editedPlacementDataVec.push_back(editData);
            }
            else
            {
                editedPlacementDataVec[0] = editData;
            }
        }
    }
    UpdateNowEditObjData();
}
/// <summary>
/// 編集中、編集済みのプレイヤーを描画
/// </summary>
void PlayerDataEditor::Draw() const
{
    //今現在編集中なら
    if (nowEditAction != EditActionKind::select)
    {
        //今編集しているエネミー
        drawer->SelectDraw(nowEditObjPlaceData);
    }
    else//編集していないいときは
    {
        //編集中じゃなくてもeditKindと同じものを選ぼうとしていたら描画
        if (nowEditObjPlaceData.objKind == CAST_I(editKind))
        {
            drawer->SelectDraw(nowEditObjPlaceData);
        }
        else
        {
            drawer->Draw(nowEditObjPlaceData);
        }
    }
}