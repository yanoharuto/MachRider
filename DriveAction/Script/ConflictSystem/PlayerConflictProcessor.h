#pragma once
#include "ConflictProcessor.h"
class PlayerCar;
/// <summary>
/// プレイヤーの衝突処理実行役
/// </summary>
class PlayerConflictProcessor : public ConflictProcessor
{
public:

    /// <summary>
    /// プレイヤーの衝突処理実行役
    /// </summary>
    PlayerConflictProcessor(PlayerCar* const car);
    ~PlayerConflictProcessor() {};
    /// <summary>
    /// 衝突結果実行役
    /// </summary>
    /// <param name="resultInfo">衝突結果</param>
    void OnConflict(CollisionResultInfo resultInfo)override;
    /// <summary>
    /// 収集アイテムにぶつかった回数
    /// </summary>
    /// <returns></returns>
    int GetCollectNum()const { return getCollectNum; };
private:
    //収集アイテムにぶつかった回数
    int getCollectNum = 0;
};

