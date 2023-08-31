#include "LittleRadiusLaserController.h"
#include "LittleRadiusLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// 小さくy軸回転するレーザーの更新役
/// </summary>
LittleRadiusLaserController::LittleRadiusLaserController()
    :DamageObjectController(ObjectInit::littleRadiusLaser)
{

};
/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>
void LittleRadiusLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new LittleRadiusLaser(std::move(sub)));
}
