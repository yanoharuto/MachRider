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
#include "EditDataSaver.h"
//今編集しているオブジェクトのポジション
PlacementData StageDataEditor::nowEditObjData = {};
/// 収集アイテムの数
int StageDataEditor::collectNum = 0;
/// 収集アイテムを取ったどのタイミングで出てくるか
int StageDataEditor::getCollectNum = 0;

/// <summary>
///ステージに配置するオブジェクトの位置などを保存する
/// </summary>
/// <param name="setFileName">どのファイルに保存するか教えて</param>
StageDataEditor::StageDataEditor(std::string setFileName, InitObjKind objKind)
{
    editKind = objKind;
    //もしすでにファイルがあるならデータを取ってくる
    placementDataVec = FirstPositionGetter::CSVConvertFirstData(setFileName,objKind);
    //編集オブジェクト
    editObject = new EditorObject();
    drawer = new EditorDrawModel(editKind);
}
/// <summary>
/// 描画役と編集オブジェクトの解放
/// </summary>
StageDataEditor::~StageDataEditor()
{
    EditDataSaver dataSaver;
    dataSaver.SaveEditData(placementDataVec, editKind);
    //描画役削除
    SAFE_DELETE(drawer);
    //編集オブジェクト
    SAFE_DELETE(editObject);
}
/// <summary>
/// 新しく編集したり過去に編集したものを再編集したりする
/// </summary>
void StageDataEditor::Update()
{
    if (nowEditAction == select)
    {
        SelectEditedObject();
        //スペースキーで編集開始
        if(UserInput::GetInputState(Space) == Push)
        {
            //selectEditedNumにNEW_EDIT_NUM以外の数字が入っているなら再編集
            nowEditAction = selectEditedNum != NEW_EDIT_NUM ? reEdit : edit;
        }
    }
    else//SpaceKeyを押して編集モードに切り替え
    {
        Edit();
    }
    //DKeyを押したら今選択している物を削除
    if (UserInput::GetInputState(DKey) == Push)
    {
        //再編集しようとしていたら
        if (nowEditAction != edit && selectEditedNum != NEW_EDIT_NUM)
        {
            //再編集中ならそれを削除
            EraceEndEditData(selectEditedNum);
            selectEditedNum = NEW_EDIT_NUM;
        }
        nowEditAction = select;
    }
    UpdateNowEditObjData();

}
/// <summary>
/// 編集中や編集し終えたオブジェクトの描画
/// </summary>
void StageDataEditor::Draw() const
{
    if (!placementDataVec.empty())
    {
        //編集済みのオブジェクト全て描画
        for (unsigned int i = 0; i < placementDataVec.size(); i++)
        {
            //描画するオブジェクトの種類
            InitObjKind drawKind = static_cast<InitObjKind>(placementDataVec[i].objKind);
            //編集済みのオブジェクトの配置や向き
            PlacementData editData = placementDataVec[i];
            //DrawKindの種類のオブジェクトの描画役
            drawer->Draw(editData);
        }
    }
    //今現在編集中なら
    if (nowEditAction != select)
    {
        //編集中のものを表示
        auto editData = editObject->GePlacementData();
        drawer->SelectDraw(editData);
    }
    //編集中じゃなくてもeditKindと同じものを選ぼうとしていたら描画
    if (nowEditObjData.objKind == editKind)
    {
        drawer->SelectDraw(nowEditObjData);
    }
}
/// <summary>
/// 今編集しているオブジェクトのポジション
/// </summary>
/// <returns></returns>
VECTOR StageDataEditor::GetEditObjPos()
{
    return  VGet(nowEditObjData.posX,0,nowEditObjData.posZ);
}
VECTOR StageDataEditor::GetEditObjDir()
{
    return VGet(nowEditObjData.dirX, 0, nowEditObjData.dirZ);
}
/// <summary>
/// 何番目のミッションか変更する
/// </summary>
void StageDataEditor::ChangeEditedCollectNum()
{
    if (UserInput::GetInputState(SKey) == Hold)
    {
        if (UserInput::GetInputState(Up) == Push)
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
        else if (UserInput::GetInputState(Down) == Push)
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
}
/// <summary>
/// 編集済みデータの削除
/// </summary>
/// <param name="eraceNum">削除するのは先頭から何番目か</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = placementDataVec.begin();
    editData += eraceNum;
    placementDataVec.erase(editData);
}

/// <summary>
/// 編集操作
/// </summary>
void StageDataEditor::Edit()
{
    //移動回転
    editObject->Update();
    //スペースキーを押したら
    if (UserInput::GetInputState(Space) == Push)
    {
        //編集したオブジェクトの位置と向きと種類
        PlacementData editData = editObject->GePlacementData();
        editData.objKind = editKind;
        //何個目のアイテムを回収したかで出てくるか設定する
        editData.collectNum = getCollectNum;
        //過去に編集していたオブジェクトを再編集していたら
        if (nowEditAction == reEdit)
        {
            //配置情報を再保存
            placementDataVec[selectEditedNum] = editData;
            selectEditedNum = NEW_EDIT_NUM;
        }
        else
        {
            //新しい編集オブジェクトをコンテナに納品
            placementDataVec.push_back(editData);
        }
        //スペースキーを押したら編集終了
        nowEditAction = select;
    }
}
/// <summary>
/// NowEditObjDataメンバ変数を更新する
/// </summary>
void StageDataEditor::UpdateNowEditObjData()
{
    //カメラに見るべきオブジェクトを伝える
    nowEditObjData = editObject->GePlacementData();
    nowEditObjData.objKind = static_cast<int>(editKind);
}
/// <summary>
/// 編集済みのオブジェクトを選択する
/// </summary>
void StageDataEditor::SelectEditedObject()
{
    //編集済みアイテムがあるなら
    if (!placementDataVec.empty())
    {
        int prevNum = selectEditedNum;
        //左キーで古い保存されたオブジェクトを引き出せるようになる
        if (UserInput::GetInputState(Left) == Push)
        {
            selectEditedNum--;
            //-1だったら新しく作ろうとしている
            if (selectEditedNum < 0)
            {
                selectEditedNum = NEW_EDIT_NUM;
                return;
            }
        }
        //右キーで一番新しい保存されたオブジェクトを引き出せるようになる
        else if (UserInput::GetInputState(Right) == Push) 
        {
            selectEditedNum++;
            //過去に編集したアイテムの数より少なくなっているか
            if (selectEditedNum >= static_cast<int>(placementDataVec.size()))
            {
                selectEditedNum = placementDataVec.size() - 1;
            }
        }
        //過去のアイテムを左右キーで選択したら
        if (selectEditedNum != prevNum)
        {
            //過去に編集したデータを所得
            PlacementData editedData = placementDataVec[selectEditedNum];
            editObject->SetArrangementData(editedData);
            getCollectNum = editedData.collectNum;
        }
    }
}