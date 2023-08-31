#include "EditManual.h"
#include "Utility.h"
#include "DxLib.h"
#include "UIDrawer.h"
#include "StageDataEditor.h"

/// <summary>
/// フォントサイズと表示位置の調整
/// </summary>
EditManual::EditManual()
{
    screenHeight = static_cast<int>(SCREEN_HEIGHT * UIDrawer::GetScreenRaito() - fontSize);
    SetFontSize(fontSize);
}
/// <summary>
/// 操作説明表示
/// </summary>
/// <param name="editor">今編集中か教えてもらう</param>
void EditManual::Draw(StageDataEditor* const editor)
{
    //表示Y位置
    int charY = screenHeight - strBetweenY;
    //オブジェクトを選択
    if (editor->IsEndEditing())
    {
        DrawString(0, charY, selectCrossKeyAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX, charY, selectSpaceKeyAction.c_str(), GetColor(0, 0, 0));
    }
    else//編集中
    {
        DrawString(0, charY, editCrossAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX, charY, editSpaceKeyAction.c_str(), GetColor(0, 0, 0));
        DrawString(strBetweenX * 2, charY, wKeyAction.c_str(), GetColor(0, 0, 0));
    }
    //カメラ操作や削除方法
    charY -= strBetweenY;
    DrawString(0, charY , aKeyAction.c_str(), GetColor(0, 0, 0));
    DrawString(strBetweenX, charY , dKeyAction.c_str(), GetColor(0, 0, 0));
    DrawString(strBetweenX * 2, charY , sKeyAction.c_str(), GetColor(0, 0, 0));
}

