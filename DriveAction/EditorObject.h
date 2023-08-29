#pragma once
#include "Object.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
/// <summary>
/// エディタ上で表示するオブジェクト
/// </summary>
class EditorObject :
    public Object
{
public:
    /// <summary>
    /// 編集したいものを引数に下さい
    /// </summary>
    EditorObject();
    ~EditorObject();
    /// <summary>
    /// 各オブジェクトを動かしたり回転させたりする
    /// </summary>
    void Update()override;
    /// <summary>
    /// 描画に必要な構造体を渡す
    /// </summary>
    /// <returns>位置と向きと描画したいオブジェクトの種類</returns>
    PlacementData GePlacementData()const;
    /// <summary>
    /// 引数の配置を引き継ぎ位置を変える
    /// </summary>
    /// <param name="setData">配置</param>
    void SetArrangementData(PlacementData setData);
protected:
    /// <summary>
    /// 入力を反映して移動と回転を更新
    /// </summary>
    void ReflectInput();
  
    //回転速度
    static const int rotaSpeed = 2;
    //移動速度
    static const int moveSpeed = 5;
};