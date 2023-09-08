#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include "EditObjectData.h"
class StageDataEditor;
class StageObjectController;
class EditorCameraObserver;

/// <summary>
/// 編集処理の流れ
/// </summary>
class EditorManager final
{
public:
    /// <summary>
    /// 編集に必要なものを確保
    /// </summary>
    EditorManager();
    /// <summary>
    /// 編集物やステージの背景などを解放
    /// </summary>
    ~EditorManager();
    /// <summary>
    /// 編集する種類や各編集物の編集
    /// </summary>
    void Update(std::weak_ptr<EditorCameraObserver> cameraObserever);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() const;
    /// <summary>
    /// 編集中かどうかを返す
    /// </summary>
    /// <returns>編集中ならTrue</returns>
    bool IsNowEdit() const;
    /// <summary>
    /// 編集物の位置や向きを共有
    /// </summary>
    PlacementData GetNowEditObjPlaceData()const;
private:
    /// <summary>
    /// 編集するものを選択
    /// </summary>
    void SelectEditKind();
    //ステージの端
    StageObjectController* stage;
    //現在編集している物
    std::shared_ptr<StageDataEditor> nowEditor;
    //編集クラスのまとめ
    std::vector<std::shared_ptr<StageDataEditor>> editorVec;
    //編集クラスの番号
    int selectEditorNum = 0;
};