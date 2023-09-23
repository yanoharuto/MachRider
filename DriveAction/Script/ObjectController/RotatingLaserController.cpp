#include "RotatingLaserController.h"
#include "RotatingLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// 追加と描画の準備
/// </summary>
/// <param name="generator">レーザー生成役</param>
RotatingLaserController::RotatingLaserController()
    :DamageObjectController(ObjectInit::InitObjKind::laser)
{
};
/// <summary>
/// レーザーを照射したオブジェクトを引数にもらう
/// </summary>
/// <param name="sub">レーザーを照射したオブジェクト</param>
void RotatingLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new RotatingLaser(std::move(sub)));
}