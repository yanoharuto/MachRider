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
void EditManual::Draw(StageDataEditor* const editor)const
{
    //描画文字Y座標
    int charY = screenHeight - strBetweenY;
    //描画文字X座標
    int charX = strBetweenX;
    //オブジェクトを選択
    if (editor->IsEndEditing())
    {
        //十字選択中説明文
        DrawManualString(selectCrossKeyAction, charX, charY);
        charX = GetNextDrawX(selectCrossKeyAction,charX);
        //SpaceKey選択中説明文
        DrawManualString(selectSpaceKeyAction, charX, charY);
        charX = GetNextDrawX(selectSpaceKeyAction, charX);
    }
    else//編集中
    {
        //十字編集中説明文
        DrawManualString(editCrossAction, charX, charY);
        charX = GetNextDrawX(editCrossAction, charX);
        //SpaceKey編集中説明文
        DrawManualString(editSpaceKeyAction, charX, charY);
        charX = GetNextDrawX(editSpaceKeyAction, charX);
        //WKeyの役割説明
        DrawManualString(wKeyAction, charX, charY);
        charX = GetNextDrawX(editSpaceKeyAction, charX);
    }
    //改行
    charY -= strBetweenY;
    charX = strBetweenX;
    //カメラ操作や削除方法
    //AKeyの役割説明
    DrawManualString(aKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //DKeyの役割説明
    DrawManualString(dKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //ESCKeyの役割説明
    DrawManualString(escKeyAction, charX, charY);
    charX = GetNextDrawX(editSpaceKeyAction, charX);
    //SKeyの役割説明
    DrawManualString(sKeyAction, charX, charY);
}
/// <summary>
/// 文字列を書くXの場所を決める
/// </summary>
/// <param name="prevStr">直前に書いた文字</param>
/// <param name="nowX">今のX座標</param>
/// <returns>次に書くべきX座標</returns>
int EditManual::GetNextDrawX(std::string prevStr, int nowX)const
{
    return static_cast<int>(prevStr.size()) * fontSize + strBetweenX + nowX;
}
/// <summary>
/// 説明文の描画
/// </summary>
/// <param name="drawStr">説明文</param>
/// <param name="x">描画位置X</param>
/// <param name="y">描画位置Y</param>
void EditManual::DrawManualString(std::string drawStr, int x, int y)const
{
    DrawString(x, y, drawStr.c_str(), GetColor(0, 0, 0));
}