#include "BigRadiusLaserController.h"
#include "BigRadiusLaser.h"
#include "ObjectObserver.h"

/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>


void BigRadiusLaserController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new BigRadiusLaser(std::move(sub)));
}