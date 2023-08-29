#include "PlayerConflictProcessor.h"
#include "PlayerCar.h"

PlayerConflictProcessor::PlayerConflictProcessor(PlayerCar* const car)
    :ConflictProcessor(car)
{
}

PlayerConflictProcessor::~PlayerConflictProcessor()
{
}
/// <summary>
/// 衝突結果実行役
/// </summary>
/// <param name="resultInfo">衝突結果</param>
void PlayerConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    //衝突後の処理を行う必要がないなら終了
    if (object == nullptr)return;
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //当たった時の処理を行う
        object->OnConflict(resultInfo);
        //コレクトアイテムならカウント
        if (resultInfo.tag == Object::collect)
        {
            getCollectNum++;
        }
    }
}