#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EditorObject.h"
#include "EditorDrawModel.h"
#include "Utility.h"
#include "StageDataManager.h"
//今編集しているオブジェクトのポジション
PlacementData StageDataEditor::nowEditObjPlaceData = {};
/// 収集アイテムの数
int StageDataEditor::collectNum = 0;
/// 収集アイテムを取ったどのタイミングで出てくるか
int StageDataEditor::getCollectNum = 0;
//編集ファイル置き場
const std::string StageDataEditor::editFilePath = "data/editFile/";
/// <summary>
///ステージに配置するオブジェクトの位置などを保存する
/// </summary>
/// <param name="setFileName">どのファイルに保存するか教えて</param>
StageDataEditor::StageDataEditor(std::string setFileName, InitObjKind objKind)
{
    editKind = objKind;
    auto a = StageDataManager::IsExistFile(editFilePath + setFileName + Utility::JSON_FILE);
    //もしすでにファイルがあるならデータを取ってくる
    editedPlacementDataVec = FirstPositionGetter::GetPlaceData(editFilePath + setFileName,objKind);
    //編集オブジェクト
    editObject = new EditorObject();
    drawer = new EditorDrawModel(editKind);
}
/// <summary>
/// 描画役と編集オブジェクトの解放
/// </summary>
StageDataEditor::~StageDataEditor()
{
    //描画役削除
    SAFE_DELETE(drawer);
    //編集オブジェクト
    SAFE_DELETE(editObject);
}
/// <summary>
/// 新しく編集したり過去に編集したものを再編集したりする
/// </summary>
void StageDataEditor::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    if (nowEditAction == EditActionKind::select)
    {
        SelectEditedObject();
        //スペースキーで編集開始
        if(UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
        {
            //selectEditedNumにNEW_EDIT_NUM以外の数字が入っているなら再編集
            nowEditAction = selectEditedNum != NEW_EDIT_NUM ? EditActionKind::reEdit : EditActionKind::edit;
        }
    }
    else//編集モード
    {
        Edit(cameraObserever);
    }
    //DKeyを押したら今選択している物を削除
    if (UserInput::GetInputState(UserInput::KeyInputKind::DKey) == UserInput::InputState::Push)
    {
        //再編集しようとしていたら
        if (nowEditAction != EditActionKind::edit && selectEditedNum != NEW_EDIT_NUM)
        {
            //再編集中ならそれを削除
            EraceEndEditData(selectEditedNum);
            selectEditedNum = NEW_EDIT_NUM;
        }
        nowEditAction = EditActionKind::select;
    }
    UpdateNowEditObjData();

}
/// <summary>
/// 編集中や編集し終えたオブジェクトの描画
/// </summary>
void StageDataEditor::Draw() const
{
    if (!editedPlacementDataVec.empty())
    {
        //編集済みのオブジェクト全て描画
        for (unsigned int i = 0; i < editedPlacementDataVec.size(); i++)
        {
            //描画するオブジェクトの種類
            InitObjKind drawKind = static_cast<InitObjKind>(editedPlacementDataVec[i].objKind);
            //編集済みのオブジェクトの配置や向き
            PlacementData editData = editedPlacementDataVec[i];
            //DrawKindの種類のオブジェクトの描画役
            drawer->Draw(editData);
        }
    }
    //今現在編集中なら
    if (nowEditAction != EditActionKind::select)
    {
        //編集中のものを表示
        auto editData = editObject->GePlacementData();
        drawer->SelectDraw(editData);
    }
    //編集中じゃなくてもeditKindと同じものを選ぼうとしていたら描画
    if (nowEditObjPlaceData.objKind == CAST_I(editKind))
    {
        drawer->SelectDraw(nowEditObjPlaceData);
    }
}


/// <summary>
/// 現在編集しているアイテムの出てくるタイミングを変更
/// </summary>
void StageDataEditor::ChangeEditedCollectNum()
{
    if (UserInput::GetInputState(UserInput::KeyInputKind::Up) == UserInput::InputState::Push)
    {
        //収集アイテムの数より多くならない
        if (getCollectNum + 1 > collectNum)
        {
            getCollectNum = collectNum;
        }
        else
        {
            getCollectNum++;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) == UserInput::InputState::Push)
    {
        //0より少なくならない
        if (getCollectNum - 1 < 0)
        {
            getCollectNum = 0;
        }
        else
        {
            getCollectNum--;
        }
    }
}
/// <summary>
/// 編集済みデータの削除
/// </summary>
/// <param name="eraceNum">削除するのは先頭から何番目か</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = editedPlacementDataVec.begin();
    editData += eraceNum;
    editedPlacementDataVec.erase(editData);
}

/// <summary>
/// 編集操作
/// </summary>
void StageDataEditor::Edit(std::weak_ptr<CameraObserver> cameraObserever)
{
    //移動回転
    editObject->Update(cameraObserever);
    //スペースキーを押したら
    if (UserInput::GetInputState(UserInput::KeyInputKind::Space) == UserInput::InputState::Push)
    {
        //編集したオブジェクトの位置と向きと種類
        PlacementData editData = editObject->GePlacementData();
        editData.objKind = CAST_I(editKind);
        //何個目のアイテムを回収したかで出てくるか設定する
        editData.collectNum = getCollectNum;
        //過去に編集していたオブジェクトを再編集していたら
        if (nowEditAction == EditActionKind::reEdit)
        {
            //配置情報を再保存
            editedPlacementDataVec[selectEditedNum] = editData;
            selectEditedNum = NEW_EDIT_NUM;
        }
        else
        {
            //新しい編集オブジェクトをコンテナに納品
            editedPlacementDataVec.push_back(editData);
        }
        //スペースキーを押したら編集終了
        nowEditAction = EditActionKind::select;
    }
}
/// <summary>
/// NowEditObjDataメンバ変数を更新する
/// </summary>
void StageDataEditor::UpdateNowEditObjData()
{
    //カメラに見るべきオブジェクトを伝える
    nowEditObjPlaceData = editObject->GePlacementData();
    nowEditObjPlaceData.objKind = static_cast<int>(editKind);
}
/// <summary>
/// 編集済みのオブジェクトを選択する
/// </summary>
void StageDataEditor::SelectEditedObject()
{
    //編集済みアイテムがあるなら
    if (!editedPlacementDataVec.empty())
    {
        int prevNum = selectEditedNum;
        //左キーで古い保存されたオブジェクトを引き出せるようになる
        if (UserInput::GetInputState(UserInput::KeyInputKind::Left) == UserInput::InputState::Push)
        {
            selectEditedNum--;
            //-1だったら新しく作ろうとしている
            if (selectEditedNum < 0)
            {
                selectEditedNum = NEW_EDIT_NUM;
                return;//処理を中断する
            }
        }
        //右キーで一番新しい保存されたオブジェクトを引き出せるようになる
        else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) == UserInput::InputState::Push)
        {
            selectEditedNum++;
            //過去に編集したアイテムの数より少なくなっているか
            if (selectEditedNum >= static_cast<int>(editedPlacementDataVec.size()))
            {
                selectEditedNum = editedPlacementDataVec.size() - 1;
            }
        }
        //過去のアイテムを左右キーで選択したら
        if (selectEditedNum != prevNum)
        {
            //過去に編集したデータを所得
            PlacementData editedData = editedPlacementDataVec[selectEditedNum];
            editObject->SetArrangementData(editedData);
            getCollectNum = editedData.collectNum;
        }
    }
}