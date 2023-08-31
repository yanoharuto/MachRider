#pragma once
#include "SceneFlowBase.h"
#include <unordered_map>
class EditorCamera;
class StageDataEditor;
class PlayerDataEditor;
class EnemyDataEditor;
class CollectItemDataEditor;
class StageObjectController;
class EditManual;
class EditorEffect;
/// <summary>
/// 編集処理の流れ
/// </summary>
class EditorSceneFlow :public SceneFlowBase
{
public:
    /// <summary>
    /// 編集プロセス
    /// </summary>
    enum EditProcessState
    {
        //player編集
        editPlayer,
        //収集アイテム編集
        editCollect,
        //敵編集
        editEnemy,
    };
    /// <summary>
    /// 編集に必要なものを確保
    /// </summary>
    EditorSceneFlow();
    /// <summary>
    /// 編集物やステージの背景などを解放
    /// </summary>
    ~EditorSceneFlow();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() const override;
private:
    /// <summary>
    /// 編集するものを選択
    /// </summary>
    void SelectEditKind();
    //ステージの端
    StageObjectController* stage;
    //編集箇所
    EditProcessState editState;
    //現在編集している物
    StageDataEditor* nowEditor;
    //編集操作説明
    EditManual* manual;
    //編集時に出てくるエフェクトの更新役
    EditorEffect* editorEffect;
    //カメラ
    EditorCamera* camera;
    //編集クラスのまとめ
    std::vector<StageDataEditor*> editorVec;
    //編集クラスの番号
    int selectEditorNum = 0;
};

