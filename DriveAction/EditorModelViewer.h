#pragma once
#include "ModelViewer.h"
#include "EditObjectData.h"
class EditorObject;
/// <summary>
/// 各編集オブジェクトの描画担当役
/// </summary>
class EditorModelViewer:public ModelViewer
{
public:
    /// <summary>
    /// 各編集オブジェクトの描画担当役
    /// </summary>
    EditorModelViewer(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 引数の場所に描画
    /// </summary>
    /// <param name="data"></param>
    virtual void Draw(EditArrangementData data)const;
    /// <summary>
    /// 編集者が選択している物の表示　若干上に上がる
    /// </summary>
    /// <param name="data"></param>
    virtual void SelectDraw(EditArrangementData data)const;
protected:

    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    /// <param name="dir"></param>
    void ModelSetMatrix(VECTOR dir) const;
    //選択されているならちょっと位置が高くなる
    const int selectPosY = 75;
    //modelのサイズ
    float mSize = 0;
};