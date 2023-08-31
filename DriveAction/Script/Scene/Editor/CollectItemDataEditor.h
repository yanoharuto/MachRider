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

    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 編集中や編集し終えたオブジェクトの描画
    /// </summary>
    void Draw()const override;

private:
    //今何個目の収集アイテムなのかの位置
    const int drawCollectNumY = 200;
    //今　何番目のミッションかの位置
    const int drawEditedCollectNumY = 0;
    //読み込む配置情報の書いてあるファイルのパス
    static const std::string loadEditFilePath;
};

