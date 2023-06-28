#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "LittleRadiusLaserController.h"
#include "BigRadiusLaserController.h"
#include "ObjectObserver.h"
#include "ActorController.h"
#include "ActorControllerManager.h"
//作成したコントローラークラス。GetControllerListが呼ばれると初期化される
std::list<ActorController*> DamageObjectGenerator::createDamageObject;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
DamageObjectGenerator::DamageObjectGenerator()
{    

}
DamageObjectGenerator::~DamageObjectGenerator()
{
}
/// <summary>
/// ダメージを与えるオブジェクトを生成
/// </summary>
/// <param name="itemTag"></param>
/// <param name="sub">発射した人の情報を渡す</param>
/// <returns></returns>
void DamageObjectGenerator::GenerateDamageObject(DamageObjectKind itemTag,ObjectSubject* sub)
{
    ActorController* obj = nullptr;
    
    switch (itemTag)
    {
    case  bomber:
        obj = new BomberController(sub);
        break;
    case littleRadLaser:
        obj = new LittleRadiusLaserController(sub);
        break;
    case bigRadLaser:
        obj = new BigRadiusLaserController(sub);
        break;
    default:
        break;
    }
    createDamageObject.push_back(obj);
}
/// <summary>
/// 生成されたオブジェクトをcontrollerManagerに追加
/// </summary>
/// <param name="controllerManager"></param>
void DamageObjectGenerator::MoveControllerList(ActorControllerManager* controllerManager)
{
    for (auto ite = createDamageObject.begin(); ite != createDamageObject.end(); ite++)
    {
        controllerManager->AddActorController(std::move(*ite));
    }
    createDamageObject.clear();
}
