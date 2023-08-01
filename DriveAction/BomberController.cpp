#include "BomberController.h"
#include "Rocket.h"
#include "ObjectObserver.h"
#include "ModelViewer.h"
/// <summary>
/// ���e����W
/// </summary>
/// <param name="sub"></param>
BomberController::BomberController()
    :DamageObjectController(ObjectInit::bomber)
{
    viewer = new ModelViewer(ObjectInit::bomber);
}
/// <summary>
/// ���e���X�V�ł���悤�ɂ���
/// </summary>
/// <param name="sub">���e�𓊉������I�u�W�F�N�g</param>
void BomberController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new Rocket(std::move(sub)));
}
