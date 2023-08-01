#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "LittleRadiusLaserController.h"
#include "BigRadiusLaserController.h"
#include "ObjectObserver.h"
#include "DamageObjectController.h"
#include "ActorControllerManager.h"
//作成したコントローラークラス。GetControllerListが呼ばれると初期化される
std::unordered_map<DamageObjectGenerator::DamageObjectKind, DamageObjectController*> DamageObjectGenerator::controllerVec;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
DamageObjectGenerator::DamageObjectGenerator(ActorControllerManager* const controllerManager)
{
    controllerVec.clear();
    controllerVec.insert(std::make_pair(bomber, new BomberController()));
    controllerVec.insert(std::make_pair(littleRadLaser, new BigRadiusLaserController()));
    controllerVec.insert(std::make_pair(bigRadLaser, new LittleRadiusLaserController()));
    
    controllerManager->AddActorController(controllerVec[bomber]);
    controllerManager->AddActorController(controllerVec[bigRadLaser]);
    controllerManager->AddActorController(controllerVec[littleRadLaser]);
}
DamageObjectGenerator::~DamageObjectGenerator()
{
    controllerVec.clear();
}
/// <summary>
/// ダメージを与えるオブジェクトを生成
/// </summary>
/// <param name="itemTag"></param>
/// <param name="sub">発射した人の情報を渡す</param>
/// <returns></returns>
void DamageObjectGenerator::GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub)
{
    controllerVec[itemTag]->AddObject(std::move(sub));
}