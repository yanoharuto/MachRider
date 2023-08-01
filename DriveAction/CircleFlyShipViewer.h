#pragma once
#include "EditorModelViewer.h"

/// <summary>
/// 円形上に陣形を組む敵の描画担当
/// </summary>
class CircleFlyShipViewer final:
    public EditorModelViewer
{
public:
    CircleFlyShipViewer();
    /// <summary>
    /// 描画する
    /// </summary>
    /// <param name="data"></param>
    void Draw(EditArrangementData data)const override;
    /// <summary>
    /// 編集中に選択されているとき若干上空に描画する
    /// </summary>
    /// <param name="data"></param>
    void SelectDraw(EditArrangementData data)const override;
private:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    void Init();
    //ユニットの数
    int uniNum = 0;
    //各ユニットの方向への角度
    float uniDirRota = 0.0f;
    //ユニット同士の距離
    float uniBetween=0.0f;
};