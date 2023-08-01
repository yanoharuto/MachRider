#pragma once
#include "SceneFlowBase.h"
#include <unordered_map>
class EditorCamera;
class StageDataEditor;
class PlayerDataEditor;
class EnemyDataEditor;
class CollectItemDataEditor;
class StageObjectController;

/// <summary>
/// 編集処理の流れ
/// </summary>
class EditorSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// 編集プロセス
    /// </summary>
    enum EditProcessState
    {
        //player編集
        EditPlayer,
        //収集アイテム編集
        EditCollect,
        //敵編集
        EditEnemy,
    };
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EditorSceneFlow();

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
    //描画する文字のサイズ
    const int fontSize = 124;
    //ステージの端
    StageObjectController* stage;
    //編集箇所
    EditProcessState editState;
    //現在編集している物
    StageDataEditor* nowEditor;
    //カメラ
    EditorCamera* camera;
    //エネミー編集クラス
    EnemyDataEditor* enemyEditor;
    //プレイヤー編集クラス
    PlayerDataEditor* playerEditor;
    //収集アイテム編集クラス
    CollectItemDataEditor* collectEditor;
};

