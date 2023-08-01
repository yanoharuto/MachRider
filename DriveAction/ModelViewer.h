#pragma once
#include "InitObjKind.h"
class Object;
/// <summary>
/// modelの描画をする役
/// </summary>
class ModelViewer
{
public:
    /// <summary>
    /// modelの描画をする役
    /// </summary>
    ModelViewer(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="drawObj">位置とか大きさとか教えてももらう</param>
    virtual void Draw(Object* drawObj) const;
protected:
    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    virtual void ModelSetMatrix(Object* drawObj) const;
    //描画モデル
    int modelHandle;
};