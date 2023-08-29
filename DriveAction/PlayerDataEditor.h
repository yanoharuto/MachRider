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
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 編集中、編集済みのプレイヤーを描画
    /// </summary>
    void Draw()const override;
private:
    //読み込む配置情報のファイルのパス
    static const std::string loadEditFilePath;
};

