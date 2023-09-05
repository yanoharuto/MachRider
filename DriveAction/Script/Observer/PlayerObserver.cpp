#include "PlayerObserver.h"
#include "PlayerCar.h"
/// <summary>
/// プレイヤーの情報を渡すやつ
/// </summary>
/// <param name="playerCar">プレイヤー</param>
PlayerObserver::PlayerObserver(PlayerCar* const playerCar)
    :ObjectObserver(playerCar)
{
    subject = playerCar;
}
/// <summary>
/// 収集アイテムを所得した回数
/// </summary>
/// <returns></returns>
int PlayerObserver::GetCollectCount()
{
    return subject->GetCollectCount();
}