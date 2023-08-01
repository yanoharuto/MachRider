#pragma once
#include "StageDataEditor.h"
/// <summary>
/// 収集アイテムの編集クラス
/// </summary>
class CollectItemDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
    /// 収集アイテムの編集クラス
    /// </summary>
    CollectItemDataEditor();
    ~CollectItemDataEditor();
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 編集済みのオブジェクトを描画
    /// </summary>
    void DrawAllEditedObject()const override;
    /// <summary>
    /// 現在編集している物を描画
    /// </summary>
    void DrawNowEditObject()const override;
    /// <summary>
    /// 文字を描画
    /// </summary>
    void DrawEditString() const override;
    /// <summary>
    /// 選択されているときの文字を描画
    /// </summary>
    void DrawSelectString()const override;
private:
    /// <summary>
    /// 編集した過去の収集アイテムを再編集できるようにする
    /// </summary>
    void SelectEditedCollect();

    //編集中の収集アイテム
    EditorObject* nowEditCollect;
    //エディターの名前の描画位置
    const int drawStrY = 600;
    //今何個目の収集アイテムなのかの位置
    const int drawCollectNumY = 200;
    //今　何番目のミッションかの位置
    const int drawMissionNumY = 0;
    //エディターが選択されたときの色
    const unsigned int selectColor = GetColor(0, 115, 250);
    //エディターの名前
    const std::string drawEditString = "Collect";
    //過去に編集した収集アイテムを選択するのに使う
    int selectEditedCollectNum = -1;
};

