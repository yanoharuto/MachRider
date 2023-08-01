#include "CollectItemDataEditor.h"
#include "EditorObject.h"
#include "UserInput.h"
#include "Utility.h"
#include "EditorModelViewer.h"
/// <summary>
/// 収集アイテムの編集するクラス
/// </summary>
CollectItemDataEditor::CollectItemDataEditor()
    :StageDataEditor("collectData.csv")
{
    nowEditCollect = new EditorObject(ObjectInit::collect);
    viewer = new EditorModelViewer(ObjectInit::collect);
}

CollectItemDataEditor::~CollectItemDataEditor()
{
    for (int i = 0; i < editDataVec.size(); i++)
    {
        SaveEditObjectData(editDataVec[i]);
    }
    SAFE_DELETE(nowEditCollect);
    SAFE_DELETE(viewer);
}
/// <summary>
/// 更新
/// </summary>
void CollectItemDataEditor::Update()
{
    if (isEndEdit)
    {

        SelectEditedCollect();
        //スペースキーで編集開始
        isEndEdit = UserInput::GetInputState(Space) != Push;
    }
    else if (!isEndEdit)//編集中
    {
        //移動回転
        nowEditCollect->Update();
        //編集終了
        if (UserInput::GetInputState(Space) == Push)
        {
            isEndEdit = true;
            //収集アイテムの情報
            auto editData = nowEditCollect->GetEditObjectData();
            //保存
            if (selectEditedCollectNum != -1)
            {
                editDataVec[selectEditedCollectNum] = editData;
                selectEditedCollectNum = -1;
            }
            else
            {
                editDataVec.push_back(editData);
            }
        }
        //破棄
        else if (UserInput::GetInputState(DKey) == Push)
        {
            if (selectEditedCollectNum != -1)//昔編集したものを破棄
            {
                EraceEndEditData(selectEditedCollectNum);
                selectEditedCollectNum = -1;
            }
            isEndEdit = true;
        }
    }
    //収集アイテムの数を他のEditorにも反映
    if (!editDataVec.empty())
    {
        collectNum = editDataVec.size() - 1;
        collectNum = collectNum < 0 ? 0 : collectNum;
    }

    //カメラに見るべきオブジェクトを伝える
    nowEditObjData = nowEditCollect->GetEditObjectData();
    UpdateEffect();
}
/// <summary>
/// 編集済みのオブジェクトを描画
/// </summary>
void CollectItemDataEditor::DrawAllEditedObject() const
{
    if (!editDataVec.empty())
    {
        for (int i = 0; i < editDataVec.size(); i++)
        {
            viewer->Draw(editDataVec[i]);
        }
    }
}
/// <summary>
/// 現在編集している物を描画
/// </summary>
void CollectItemDataEditor::DrawNowEditObject() const
{
    viewer->SelectDraw(nowEditCollect->GetEditObjectData());
}
/// <summary>
/// 文字を描画
/// </summary>
void CollectItemDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
    //収集アイテムの数
    DrawString(0, drawCollectNumY, std::to_string(collectNum).c_str(), GetColor(0, 0, 0));
    //ミッションの数
    DrawString(0, drawMissionNumY, std::to_string(missionNum).c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// 選択されているときの文字を描画
/// </summary>
void CollectItemDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}

/// <summary>
/// 編集した過去の収集アイテムを再編集できるようにする
/// </summary>
void CollectItemDataEditor::SelectEditedCollect()
{
    //編集済みアイテムがあるなら
    if (!editDataVec.empty())
    {
        int prevNum = selectEditedCollectNum;
        //左右キーで再編集するものを変更
        if (UserInput::GetInputState(Left) == Push) selectEditedCollectNum--;
        else if (UserInput::GetInputState(Right) == Push) selectEditedCollectNum++;
        //過去のアイテムを上下キーで選択したら
        if (selectEditedCollectNum > -1 && selectEditedCollectNum != prevNum)
        {
            //過去に編集したアイテムの数より少なくなっているか
            if (selectEditedCollectNum >= editDataVec.size())
            {    
                selectEditedCollectNum = editDataVec.size() - 1;
            }
            //過去に編集したデータを所得
            auto editedData = editDataVec[selectEditedCollectNum];
            SAFE_DELETE(nowEditCollect);
            nowEditCollect = new EditorObject(editedData);
        }
        else if(selectEditedCollectNum < -1)//-1だったら新しく作ろうとしている
        {
            selectEditedCollectNum = -1;
        }
    }
}
