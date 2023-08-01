#include "PlayerDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorModelViewer.h"

/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
PlayerDataEditor::PlayerDataEditor()
    :StageDataEditor("playerData.csv")
{
    if (editDataVec.empty())
    {
        player = new EditorObject(ObjectInit::player);
    }
    else
    {
        player = new EditorObject(editDataVec[0]);
    }
    viewer = new EditorModelViewer(ObjectInit::player);
}

PlayerDataEditor::~PlayerDataEditor()
{
    SaveEditObjectData(player->GetEditObjectData());
    SAFE_DELETE(player);
}
/// <summary>
/// 更新
/// </summary>
void PlayerDataEditor::Update()
{
    if (isEndEdit)
    {
        //スペースキーで編集開始
        isEndEdit = UserInput::GetInputState(Space) != Push;
    }
    else if (!isEndEdit)
    {
        //移動回転
        player->Update();
        //編集終了
        if (UserInput::GetInputState(Space) == Push)
        {
            isEndEdit = true;
        }
    }
    //カメラに見るべきオブジェクトを伝える
    nowEditObjData = player->GetEditObjectData();
    UpdateEffect();
}
/// <summary>
/// プレイヤーの描画
/// </summary>
void PlayerDataEditor::DrawNowEditObject() const
{
    viewer->SelectDraw(player->GetEditObjectData());
}
/// <summary>
/// プレイヤーの描画
/// </summary>
void PlayerDataEditor::DrawAllEditedObject() const
{
    if (isEndEdit)
    {
        viewer->Draw(player->GetEditObjectData());
    }
}
/// <summary>
/// 文字を描画
/// </summary>
void PlayerDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// 選択されているときの文字を描画
/// </summary>
void PlayerDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}
