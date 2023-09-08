#pragma once
#include "EditObjectData.h"
class StageDataEditor;
/// <summary>
/// Editorで使うエフェクト
/// </summary>
class EditorEffect
{
public:
    /// <summary>
    /// エフェクト読み込み
    /// </summary>
    EditorEffect();
    /// <summary>
    /// エフェクト終了
    /// </summary>
    ~EditorEffect();
    /// <summary>
    /// エフェクトの向きと位置の変更
    /// </summary>
    /// <param name="editObjPlaceData">今編集しているオブジェクトの位置</param>
    void Update(PlacementData const editObjPlaceData);
private:
    //配置中のオブジェクトの向きが分かるエフェクトのサイズ
    const float dirEffectSize = 5.0f;
    //編集物の位置の分かりやすくなるエフェクト
    int posEffect = -1;
    //向きが分かりやすくなるエフェクト
    int dirEffect = -1;
};