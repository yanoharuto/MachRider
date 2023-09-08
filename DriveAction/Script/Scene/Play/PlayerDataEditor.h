#pragma once
#include "StageDataEditor.h"
/// <summary>
/// プレイヤーの初期位置の編集
/// </summary>
class PlayerDataEditor final: public StageDataEditor
{
public:
    /// <summary>
    /// プレイヤーの初期位置の編集
    /// </summary>
    PlayerDataEditor();
    /// <summary>
    /// 更新
    /// </summary>
    void Update(std::weak_ptr<EditorCameraObserver> cameraObserever)override;
    /// <summary>
    /// 編集中、編集済みのプレイヤーを描画
    /// </summary>
    void Draw()const override;
private:
    //読み込むプレイヤーの位置や向きが入ったファイルのパス
    static const std::string loadEditFilePath;
};

