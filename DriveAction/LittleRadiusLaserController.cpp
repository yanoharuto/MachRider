#include "LittleRadiusLaserController.h"
#include "LittleRadiusLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>
void LittleRadiusLaserController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new LittleRadiusLaser(std::move(sub)));
}
