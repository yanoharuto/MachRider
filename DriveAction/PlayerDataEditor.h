#pragma once
#include "StageDataEditor.h"
/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
class PlayerDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
    /// プレイヤーの初期位置の編集
    /// </summary>
    PlayerDataEditor();
    ~PlayerDataEditor();
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// プレイヤーの描画
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// プレイヤーの描画
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// 文字を描画
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// 選択されているときの文字を描画
    /// </summary>
    void DrawSelectString()const override;
private:
    //プレイヤー
    EditorObject* player;
    const int drawStrY = 400;
    unsigned int selectColor = GetColor(255, 0, 0);
    std::string drawEditString = "Player";
};

