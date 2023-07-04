#pragma once
#include "UIManager.h"

class PlayManualUI
{
public:
    /// <summary>
    /// 移動方法UIの表示
    /// </summary>
    PlayManualUI();
    ~PlayManualUI();
    /// <summary>
    /// プレイヤーの入力によってUI変更
    /// </summary>
    void Update();
    /// <summary>
    /// 操作方法を描画
    /// </summary>
    void Draw() const;
private:
    //操作説明のUI情報
    UIData manualData;
};

