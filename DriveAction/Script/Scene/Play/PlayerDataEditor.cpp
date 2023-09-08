#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorDrawModel.h"
#include "Utility.h"
//読み込むプレイヤーの位置や向きが入ったファイルのパス
const std::string PlayerDataEditor::loadEditFilePath = "playerData.csv";
/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor(loadEditFilePath,player)
{
    if (!placementDataVec.empty())
    {
        editObject->SetArrangementData(placementDataVec[0]);
    }
    
}

/// <summary>
/// 更新
/// </summary>
void PlayerDataEditor::Update(std::weak_ptr<EditorCameraObserver> cameraObserever)
{
    if (nowEditAction == select && UserInput::GetInputState(Space) == Push)
    {
        //スペースキーで編集開始
        nowEditAction = edit;
    }
    else if (nowEditAction == edit)
    {
        //移動回転
        editObject->Update(cameraObserever);
        //編集終了
        if (UserInput::GetInputState(Space) == Push)
        {
            nowEditAction = select;
            PlacementData editData = editObject->GePlacementData();
            editData.objKind = editKind;
            if(placementDataVec.empty())
            {
                placementDataVec.push_back(editData);
            }
            else
            {
                placementDataVec[0] = editData;
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
    if (nowEditAction != select)
    {
        //今編集しているエネミー
        drawer->SelectDraw(nowEditObjPlaceData);
    }
    else//編集していないいときは
    {
        //編集中じゃなくてもeditKindと同じものを選ぼうとしていたら描画
        if (nowEditObjPlaceData.objKind == editKind)
        {
            drawer->SelectDraw(nowEditObjPlaceData);
        }
        else
        {
            drawer->Draw(nowEditObjPlaceData);
        }
    }
}