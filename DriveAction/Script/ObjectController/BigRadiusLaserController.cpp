#include "BigRadiusLaserController.h"
#include "BigRadiusLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// 初期化
/// </summary>
BigRadiusLaserController::BigRadiusLaserController()
    :DamageObjectController(ObjectInit::bigRadiusLaser)
{
};
/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>
void BigRadiusLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new BigRadiusLaser(std::move(sub)));
}