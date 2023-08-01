#include "BomberController.h"
#include "Rocket.h"
#include "ObjectObserver.h"
#include "ModelViewer.h"
/// <summary>
/// 爆弾制御係
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::bomber)
{
    viewer = new ModelViewer(ObjectInit::bomber);
}
/// <summary>
/// 爆弾を更新できるようにする
/// </summary>
/// <param name="sub">爆弾を投下したオブジェクト</param>
void BomberController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new Rocket(std::move(sub)));
}
