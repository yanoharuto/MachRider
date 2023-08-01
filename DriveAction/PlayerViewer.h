#pragma once
#include "ModelViewer.h"
class PlayerCar;
/// <summary>
/// プレイヤーの機体の傾きなどに対応するViewer
/// </summary>
class PlayerViewer :
    public ModelViewer
{
public:
    /// <summary>
    /// プレイヤーの機体の傾きなどに対応するViewer
    /// </summary>
    PlayerViewer();
    /// <summary>
    /// プレイヤーの角度に合わせて回転する
    /// </summary>
    /// <param name="drawObj"></param>
    void Draw(PlayerCar* drawObj) const;
protected:
    /// <summary>
/// 描画モデルの行列をセット
/// </summary>
    void ModelSetMatrix(PlayerCar* player) const;
};

